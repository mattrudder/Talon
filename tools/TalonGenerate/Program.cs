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
				if (args.Length < 3)
					throw new ArgumentException("args");

				Mode mode;
				if (Enum.TryParse(args[0], true, out mode))
				{
					switch (mode)
					{
					case Mode.Generate:
						GenerateTypeHierarchy(args[1], args[2]);
						break;
					default:
						throw new NotImplementedException("Program mode not implemented.");
					}
				}
			}
			catch (Exception e)
			{
				Console.WriteLine(e);
				PrintUsage();
			}
		}

		static void PrintUsage()
		{
			Console.WriteLine("TODO: Usage");
		}

		static void GenerateTypeHierarchy(string classTypeName, string name)
		{
			ClassType classType;
			if (Enum.TryParse(classTypeName, true, out classType))
			{
				List<string> kinds = s_filesForType[classType];

				// TODO: Generate boilerplate files for all folders in s_filesForType.
				if (!Directory.Exists("tmp"))
					Directory.CreateDirectory("tmp");

				foreach (TemplateModel template in s_listTemplates)
				{
					string templatePath = ResolveTemplatePath(template.TemplateFile);
					if (templatePath == null)
						continue;

					s_textHost.TemplateFile = Path.GetFullPath(templatePath);
					string templateText = File.ReadAllText(s_textHost.TemplateFile);
					if (string.IsNullOrEmpty(templateText))
					{
						Console.Error.WriteLine("Unable to load template.");
						continue;
					}


					// BaseClass
					// BaseClassHeaderFile
					TypeModel model = new TypeModel
					{
						Name = name,
						Type = classType,
						Kind = "Base",
						Class = string.Format("{0}Base", name),
						HeaderFile = string.Format("{0}/Base/{1}Base.h", classType, name),
						Namespaces = new [] { "Talon" },

					};
					s_textHost.Model = model;

					GenerateFile(Path.Combine(template.OutputPath, string.Format("{0}/Base/{1}Base" + template.FileExtension, classType, name)), templateText);
					
					//foreach (string kind in kinds)
					//{

					//}
				}
			}
		}

		private static void GenerateFile(string filePath, string templateText)
		{
			if (filePath == null)
				throw new ArgumentNullException("filePath");
			if (templateText == null)
				throw new ArgumentNullException("templateText");
			
			string templateOutput = s_textEngine.ProcessTemplate(templateText, s_textHost);
			//if (s_textHost.TemplateErrors.HasErrors)
			//{
			//	foreach (CompilerError error in s_textHost.TemplateErrors)
			//		Console.Error.WriteLine(error.ErrorText);

			//	break;
			//}

			using (TextWriter tw = new StreamWriter(filePath))
			{
				Console.WriteLine("Generating {0}...", Path.GetFileName(filePath));
				tw.Write(templateOutput);
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
					OutputPath = "include/Talon",
					FileExtension = ".h"
				},
				new TemplateModel 
				{
					TemplateFile = "TalonSourceFile.t4",
					OutputPath = "src/Talon",
					FileExtension = ".cpp"
				}
			};
			s_filesForType = new Dictionary<ClassType, List<string>>()
			{
				{ ClassType.Platforms, new List<string>() { "Win32" }},
				{ ClassType.Graphics, new List<string>() { "Direct3D11" }},
			};
		}

		private static readonly Dictionary<ClassType, List<string>> s_filesForType;
		private static readonly List<TemplateModel> s_listTemplates;
		private static readonly Engine s_textEngine;
		private static readonly WrapperTemplateHost s_textHost;
		private static string s_outputPath;
	}

	public struct TemplateModel
	{
		public string TemplateFile;
		public string OutputPath;
		public string FileExtension;
	}

	public struct TypeModel
	{
		public string Name;
		public ClassType Type;
		public string Kind;
		public string Class;
		public string HeaderFile;
		public string BaseClass;
		public string BaseClassHeaderFile;
		public string[] Namespaces;
	}

	internal enum Mode
	{
		Generate
	}

	public enum ClassType
	{
		Platforms,
		Graphics
	}
}
