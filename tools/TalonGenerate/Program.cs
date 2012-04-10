using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.VisualStudio.TextTemplating;
using System.Reflection;

namespace TalonGenerate
{
	class Program
	{
		static void Main(string[] args)
		{
			try
			{
				if (args.Length < 2)
					throw new ArgumentException("args");

				Mode mode;
				if (Enum.TryParse(args[0], true, out mode))
				{
					GenerateTypeHierarchy(args[1], args[2], mode);
				}
				else // Generation mode not specified.
				{
					GenerateTypeHierarchy(args[0], args[1], Mode.Update);
				}
			}
			catch (Exception e)
			{
				PrintUsage();
			}
		}

		static void PrintUsage()
		{
			Console.Error.WriteLine("TalonGenerate: Generates boilerplate code for compile-time polymorphic");
			Console.Error.WriteLine("abstractions for platform features.");
			Console.Error.WriteLine("");
			Console.Error.WriteLine("Usage: TalonGenerate [mode] <subsystem> <class>");
			Console.Error.WriteLine(" mode: ({0}; default is update) Sets the mode of generation.", string.Join("|", Enum.GetNames(typeof(Mode)).Select(s => s.ToLower())));
			Console.Error.WriteLine("   generate: Regenerates all files for all platforms.");
			Console.Error.WriteLine("   update: Updates the class hierarchy, adding new files for recently added");
			Console.Error.WriteLine("   platforms.");
			Console.Error.WriteLine("   delete: Deletes the class hierarchy for the provided class name.");
			Console.Error.WriteLine(" subsystem: ({0}) The category of grouped system functionality", string.Join("|", Enum.GetNames(typeof(ClassType)).Select(s => s.ToLower())));
			Console.Error.WriteLine(" to add the class.");
			Console.Error.WriteLine(" class: The name of the class hierarchy to generate.");
			Console.Error.WriteLine(" (For example: Window or Texture)");
			Console.Error.WriteLine("");
			Console.Error.WriteLine("Examples:");
			Console.Error.WriteLine("  Updates the Window class to add support for a new platform:");
			Console.Error.WriteLine("  TalonGenerate update platform Window");
			Console.Error.WriteLine("  --");
			Console.Error.WriteLine("  Generates Texture class, for all supported platforms:");
			Console.Error.WriteLine("  TalonGenerate graphics Texture");
		}

		static void GenerateTypeHierarchy(string classTypeName, string name, Mode generationMode)
		{
			ClassType classType;
			if (Enum.TryParse(classTypeName, true, out classType))
			{
				List<PlatformModel> kinds = s_filesForType[classType];
				foreach (TemplateModel template in s_listTemplates)
				{
					string templatePath = ResolveTemplatePath(template.TemplateFile);
					if (templatePath == null)
						continue;

					s_textHost.TemplateFile = Path.GetFullPath(templatePath);
					string templateText = File.ReadAllText(s_textHost.TemplateFile, Encoding.UTF8);
					if (string.IsNullOrEmpty(templateText))
					{
						Console.Error.WriteLine("Unable to load template.");
						continue;
					}

					string baseClass = string.Format("{0}Base", name);
					string baseFileDirectory = string.Format("{0}/Base", classType);
					string baseFileName = baseFileDirectory + "/" + baseClass;
					string baseFilePath = Path.Combine(template.OutputPath, baseFileName + template.FileExtension);

					if (generationMode == Mode.Generate)
					{
						if (!Directory.Exists(Path.Combine(template.OutputPath, baseFileDirectory)))
							Directory.CreateDirectory(Path.Combine(template.OutputPath, baseFileDirectory));

						s_textHost.Model = new TypeModel
						{
							Type = classType,
							Kind = "Base",
							Class = baseClass,
							HeaderFile = baseFileName + ".h",
							Namespaces = new[] { "Talon" },
						};

						GenerateFile(baseFilePath, templateText);
					}
					else if (generationMode == Mode.Delete)
					{
						DeleteFile(baseFilePath);
					}

					string concreteFileName = string.Format("{0}/{1}", classType, name);
					List<TypeModel> models = new List<TypeModel>();
					foreach (PlatformModel kind in kinds)
					{
						string className = string.Format("{0}{1}", kind.ShortName, name);
						string classFileDirectory = string.Format("{0}/{1}", classType, kind.FullName);
						string classFileName = classFileDirectory + "/" + className;

						if (!Directory.Exists(Path.Combine(template.OutputPath, classFileDirectory)))
							Directory.CreateDirectory(Path.Combine(template.OutputPath, classFileDirectory));

						s_textHost.Model = new TypeModel
						{
							Type = classType,
							Kind = kind.FullName,
							Class = className,
							BaseClass = baseClass,
							BaseClassHeaderFile = baseFileName + ".h",
							HeaderFile = classFileName + ".h",
							Namespaces = new[] { "Talon", kind.FullName },
						};

						models.Add(new TypeModel
							{
								Type = classType,
								Kind = kind.FullName,
								Class = name,
								BaseClass = className,
								BaseClassHeaderFile = classFileName + ".h",
								HeaderFile = concreteFileName + ".h",
								Namespaces = new[] { "Talon" },
								Conditional = kind.Conditional,
							});

						// Only generate the concrete file if not in update mode.
						string filePath = Path.Combine(template.OutputPath, classFileName + template.FileExtension);
						if (generationMode == Mode.Delete)
							DeleteFile(filePath);
						else if (!File.Exists(filePath) || generationMode == Mode.Generate)
							GenerateFile(filePath, templateText);
					}

					s_textHost.AllModels = models;

					// Write concrete class definition.
					string concreteFilePath = Path.Combine(template.OutputPath, concreteFileName + template.FileExtension);
					templatePath = ResolveTemplatePath(template.ConcreteTemplateFile);
					if (templatePath == null)
						continue;

					s_textHost.TemplateFile = Path.GetFullPath(templatePath);
					templateText = File.ReadAllText(s_textHost.TemplateFile, Encoding.UTF8);
					if (string.IsNullOrEmpty(templateText))
					{
						Console.Error.WriteLine("Unable to load template.");
						continue;
					}

					s_textHost.Model = new TypeModel
					{
						Class = name,
						HeaderFile = concreteFileName + ".h",
						Namespaces = new [] { "Talon" }
					};

					// Concreate implementation is re-written, unless we're deleting the type altogether.
					if (generationMode == Mode.Delete)
						DeleteFile(concreteFilePath);
					else
						GenerateFile(concreteFilePath, templateText);
				}
			}
		}

		private static void GenerateFile(string filePath, string templateText)
		{
			if (filePath == null)
				throw new ArgumentNullException("filePath");
			if (templateText == null)
				throw new ArgumentNullException("templateText");

			filePath = filePath.Replace(Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar);

			string templateOutput = s_textEngine.ProcessTemplate(templateText, s_textHost);
			using (TextWriter tw = new StreamWriter(filePath))
			{
				Console.WriteLine("Generating {0}...", filePath);
				tw.Write(templateOutput);
			}
		}

		private static void DeleteFile(string filePath)
		{
			if (filePath == null)
				throw new ArgumentNullException("filePath");

			filePath = filePath.Replace(Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar);
			if (File.Exists(filePath))
			{
				Console.WriteLine("Deleting {0}...", filePath);
				File.Delete(filePath);
			}
		}

		private static string ResolveTemplatePath(string templatePath)
		{
			// First, assume absolute path...
			string templatePathFull = null;
			if (!File.Exists(templatePath))
			{
				// ... then, check for a Templates directory in the current path...
				templatePathFull = Path.Combine(Directory.GetCurrentDirectory(), Path.Combine("Templates", templatePath));
				if (!File.Exists(templatePathFull))
				{
					// ... fallback to the Templates directory in the executable directory.
					string assemblyPath = Assembly.GetExecutingAssembly().Location;
					templatePathFull = Path.Combine(Path.GetDirectoryName(assemblyPath), Path.Combine("Templates", templatePath));
					if (!File.Exists(templatePathFull))
					{
						Console.Error.WriteLine("Unable to locate template path.");
						templatePathFull = null;
					}
				}
			}

			return templatePathFull;
		}

		static Program()
		{
			s_textEngine = new Engine();
			s_textHost = new WrapperTemplateHost();
			s_outputPath = Path.Combine(Directory.GetCurrentDirectory(), "include/Talon");
			s_listTemplates = new List<TemplateModel>
			{ 
				new TemplateModel 
				{
					TemplateFile = "TalonHeaderFile.t4",
					ConcreteTemplateFile = "TalonConcreteHeaderFile.t4",
					OutputPath = "include/Talon",
					FileExtension = ".h"
				},
				new TemplateModel 
				{
					TemplateFile = "TalonSourceFile.t4",
					ConcreteTemplateFile = "TalonConcreteSourceFile.t4",
					OutputPath = "src/Talon",
					FileExtension = ".cpp"
				}
			};

			// NOTE: The way the template generation works, there can only be one platform without a Conditional set, and it must be at the end of the list!
			s_filesForType = new Dictionary<ClassType, List<PlatformModel>>()
			{
				{
					ClassType.Platform,
					new List<PlatformModel>() 
					{
						new PlatformModel
						{
							FullName = "Win32",
							ShortName = "Win32",
							Conditional = "TALON_WINDOWS"
						},
						new PlatformModel
						{
							FullName = "Mac",
							ShortName = "Mac",
							Conditional = "TALON_MAC"
						},
					}
				},
				{
					ClassType.Graphics, 
					new List<PlatformModel>()
					{
						new PlatformModel
						{
							FullName = "Direct3D11",
							ShortName = "D3D11",
							Conditional = "TALON_WINDOWS"
						},
						new PlatformModel
						{
							FullName = "OpenGL",
							ShortName = "GL"
						},
					}
				}
			};
		}

		private static readonly Dictionary<ClassType, List<PlatformModel>> s_filesForType;
		private static readonly List<TemplateModel> s_listTemplates;
		private static readonly Engine s_textEngine;
		private static readonly WrapperTemplateHost s_textHost;
		private static string s_outputPath;
	}

	public struct PlatformModel
	{
		public string FullName;
		public string ShortName;
		public string Conditional;
	}

	public struct TemplateModel
	{
		public string TemplateFile;
		public string ConcreteTemplateFile;
		public string OutputPath;
		public string FileExtension;
	}

	public struct TypeModel
	{
		public ClassType Type;
		public string Kind;
		public string Class;
		public string HeaderFile;
		public string BaseClass;
		public string BaseClassHeaderFile;
		public string[] Namespaces;
		public string Conditional;
	}

	internal enum Mode
	{
		Generate,
		Update,
		Delete
	}

	public enum ClassType
	{
		Platform,
		Graphics
	}
}
