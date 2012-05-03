using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TextTemplating;
using Talon.CodeGenerator.Generators.Model;
using System.Reflection;

namespace Talon.CodeGenerator.Generators.CPlusPlus
{
    internal sealed class CPlusPlusGenerator : IGenerator
    {
		public CPlusPlusGenerator()
		{
			m_textEngine = new Engine();
			m_textHost = new CPlusPlusTemplateHost();
		}


        public void Generate(InterfaceModel model)
        {
			string includePath = string.Format("include/Talon/{0}/{1}.h", model.Module, model.Name);
			string sourcePath = string.Format("src/Talon/{0}/{1}.cpp", model.Module, model.Name);

			Generate("TalonConcreteHeaderFile.t4", includePath, model);
			Generate("TalonConcreteSourceFile.t4", sourcePath, model);

			foreach (PlatformModel platform in model.Platforms)
			{
				includePath = string.Format("include/Talon/{0}/{1}/{2}.h", model.Module, platform.ShortName, platform.ClassName);
				sourcePath = string.Format("src/Talon/{0}/{1}/{2}.cpp", model.Module, platform.ShortName, platform.ClassName);

				Generate("TalonPlatformHeaderFile.t4", includePath, platform);
				Generate("TalonPlatformSourceFile.t4", sourcePath, platform);
			}

			includePath = string.Format("include/Talon/{0}/Base/{1}Base.h", model.Module, model.Name);
			sourcePath = string.Format("src/Talon/{0}/Base/{1}Base.cpp", model.Module, model.Name);

			Generate("TalonBaseHeaderFile.t4", includePath, model);
			Generate("TalonBaseSourceFile.t4", sourcePath, model);
		}

		private void Generate(string templatePath, string outputPath, PlatformModel platform)
		{
			if (templatePath == null)
				throw new ArgumentNullException("templatePath");
			if (outputPath == null)
				throw new ArgumentNullException("outputPath");

			m_textHost.CurrentInterface = null;
			m_textHost.CurrentPlatform = platform;

			m_textHost.TemplateFile = ResolveTemplatePath(templatePath);
			string templateText = GetTemplateText(m_textHost.TemplateFile);

			GenerateFile(outputPath, templateText);
		}

		private void Generate(string templatePath, string outputPath, InterfaceModel model)
		{
			if (templatePath == null)
				throw new ArgumentNullException("templatePath");
			if (outputPath == null)
				throw new ArgumentNullException("outputPath");

			m_textHost.CurrentInterface = model;
			m_textHost.CurrentPlatform = null;

			m_textHost.TemplateFile = ResolveTemplatePath(templatePath);
			string templateText = GetTemplateText(m_textHost.TemplateFile);

			GenerateFile(outputPath, templateText);
		}

		private string GetTemplateText(string templatePath)
		{
			if (templatePath == null)
				throw new ArgumentNullException("templatePath");

			string templateText = File.ReadAllText(templatePath, Encoding.UTF8);
			if (string.IsNullOrEmpty(templateText))
			{
				Console.Error.WriteLine("Unable to load template.");
				return string.Empty;
			}

			return templateText;
		}
        
		private void GenerateFile(string filePath, string templateText)
		{
			if (filePath == null)
				throw new ArgumentNullException("filePath");
			if (templateText == null)
				throw new ArgumentNullException("templateText");

			filePath = filePath.Replace(Path.AltDirectorySeparatorChar, Path.DirectorySeparatorChar);

			string templateOutput = m_textEngine.ProcessTemplate(templateText, m_textHost);
			if (templateOutput != null)
			{
				using (TextWriter tw = new StreamWriter(filePath))
				{
					Console.WriteLine("Generating {0}...", filePath);
					tw.Write(templateOutput);
				}
			}
		}

		private static string ResolveTemplatePath(string templatePath)
		{
			// First, assume absolute path...
			string templatePathFull = null;
			if (!File.Exists(templatePath))
			{
				// ... then, check for a Templates directory in the current path...
				templatePathFull = Path.Combine(Directory.GetCurrentDirectory(), Path.Combine("Templates/CPlusPlus", templatePath));
				if (!File.Exists(templatePathFull))
				{
					// ... fallback to the Templates directory in the executable directory.
					string assemblyPath = Assembly.GetExecutingAssembly().Location;
					templatePathFull = Path.Combine(Path.GetDirectoryName(assemblyPath), Path.Combine("Templates/CPlusPlus", templatePath));
					if (!File.Exists(templatePathFull))
					{
						Console.Error.WriteLine("Unable to locate template path.");
						templatePathFull = null;
					}
				}
			}

			return templatePathFull;
		}


		private readonly Engine m_textEngine;
		private readonly CPlusPlusTemplateHost m_textHost;

		public string OutputPath { get; set; }
	}
}
