using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using Microsoft.VisualStudio.TextTemplating;

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
			catch (Exception)
			{
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

				foreach (string template in s_listTemplates)
				{
					string templatePath = ResolveTemplatePath(template);
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
						HeaderFile = string.Format("Base/{0}/{1}Base.h", classType, name),
						Namespaces = new [] { "Talon" },

					};
					s_textHost.Model = model;

					GenerateFile(string.Format("tmp/Base/{0}Base", name), templateText);
					
					//foreach (string kind in kinds)
					//{

					//}
				}
			}
		}

		private static void GenerateFile(string filePath, string templateText)
		{
			string templateOutput = s_textEngine.ProcessTemplate(templateText, s_textHost);
			//if (s_textHost.TemplateErrors.HasErrors)
			//{
			//	foreach (CompilerError error in s_textHost.TemplateErrors)
			//		Console.Error.WriteLine(error.ErrorText);

			//	break;
			//}

			string generatedPath = Path.Combine(s_outputPath, filePath);
			using (TextWriter tw = new StreamWriter(generatedPath))
			{
				Console.WriteLine("Generating {0}...", Path.GetFileName(generatedPath));
				tw.Write(templateOutput);
			}
		}

		private static string ResolveTemplatePath(string templatePath)
		{
			if (!File.Exists(templatePath))
			{
				templatePath = Path.Combine(Directory.GetCurrentDirectory(), Path.Combine("Templates", templatePath));
				if (!File.Exists(templatePath))
				{
					Console.Error.WriteLine("Unable to locate template path.");
					templatePath = null;
				}
			}

			return templatePath;
		}

		static Program()
		{
			s_textEngine = new Engine();
			s_textHost = new WrapperTemplateHost();
			s_outputPath = Path.Combine(Directory.GetCurrentDirectory(), "../../include/Generated");
			s_listTemplates = new List<string> { "TalonHeaderFile.t4", "TalonSourceFile.t4" };
			s_filesForType = new Dictionary<ClassType, List<string>>()
			{
				{ ClassType.Platform, new List<string>() { "Win32" }},
				{ ClassType.Graphics, new List<string>() { "Direct3D11" }},
			};
		}

		private static readonly Dictionary<ClassType, List<string>> s_filesForType;
		private static readonly List<string> s_listTemplates;
		private static readonly Engine s_textEngine;
		private static readonly WrapperTemplateHost s_textHost;
		private static string s_outputPath;
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
		Platform,
		Graphics
	}
}
