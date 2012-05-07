using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TextTemplating;
using Talon.CodeGenerator.Generators.Model;
using System.Reflection;
using AutoMapper;
using Talon.CodeGenerator.Parsing.Model;
using System.Text.RegularExpressions;

namespace Talon.CodeGenerator.Generators.CPlusPlus
{
    public sealed class CPlusPlusGenerator : IGenerator
    {
		public CPlusPlusGenerator()
		{
			m_textEngine = new Engine();
			m_textHost = new CPlusPlusTemplateHost();
			m_textHost.Generator = this;

			Mapper.CreateMap<string, TypeModel>().ConstructUsing(GetCPlusPlusType);
		}

        public void Generate(InterfaceModel model)
        {
            string includePath = Path.Combine(OutputPath, string.Format("include/Talon/{0}/{1}.h", model.Module, model.Name));
			string sourcePath = Path.Combine(OutputPath, string.Format("src/Talon/{0}/{1}.cpp", model.Module, model.Name));

			Generate("TalonConcreteHeaderFile.t4", includePath, model);

            // Always regenerate concrete method header, if interface was updated.
            includePath = Path.Combine(OutputPath, string.Format("include/Talon/{0}/Generated/{1}.h", model.Module, model.Name));
            Generate("TalonConcreteGeneratedHeaderFile.t4", includePath, model, GenerationOptions.AllowOverwrite);

			Generate("TalonConcreteSourceFile.t4", sourcePath, model);

			foreach (PlatformModel platform in model.Platforms)
			{
				includePath = Path.Combine(OutputPath, string.Format("include/Talon/{0}/{1}/{2}.h", model.Module, platform.Name, platform.ClassName));
				sourcePath = Path.Combine(OutputPath, string.Format("src/Talon/{0}/{1}/{2}.{3}", model.Module, platform.Name, platform.ClassName, platform.CPlusPlusExtension));

				Generate("TalonPlatformHeaderFile.t4", includePath, platform);

                // Always regenerate platform method header, if interface was updated.
                includePath = Path.Combine(OutputPath, string.Format("include/Talon/{0}/{1}/Generated/{2}.h", model.Module, platform.Name, platform.ClassName));
                Generate("TalonPlatformGeneratedHeaderFile.t4", includePath, platform, GenerationOptions.AllowOverwrite);

				Generate("TalonPlatformSourceFile.t4", sourcePath, platform);
			}

			includePath = Path.Combine(OutputPath, string.Format("include/Talon/{0}/Base/{1}Base.h", model.Module, model.Name));
			sourcePath = Path.Combine(OutputPath, string.Format("src/Talon/{0}/Base/{1}Base.cpp", model.Module, model.Name));

            // Always regenerate base class definitions, if interface was updated
            Generate("TalonBaseHeaderFile.t4", includePath, model, GenerationOptions.AllowOverwrite);
            Generate("TalonBaseSourceFile.t4", sourcePath, model, GenerationOptions.AllowOverwrite);
		}

		public string GetFieldName(PropertyModel property)
		{
			return string.Format("m_{0}{1}", char.ToLowerInvariant(property.Name[0]), property.Name.Substring(1));
		}

        public string GetSetterName(PropertyModel property)
        {
            return string.Format("Set{0}", property.Name);
        }

        public string GetGetterName(PropertyModel property)
        {
            if (string.Equals(property.Type.UnderlyingType, "bool", StringComparison.InvariantCultureIgnoreCase))
                return string.Format("Is{0}", property.Name);
            else
                return string.Format("Get{0}", property.Name);
        }

		private TypeModel GetCPlusPlusType(string definitionType)
		{
			TypeModel actualType;
            if (!s_definitionsToCppTypes.TryGetValue(definitionType, out actualType))
            {
                actualType = new TypeModel { ParameterType = definitionType, FieldType = definitionType };

                Match weakMatch = s_rgWeakReference.Match(definitionType);
                if (weakMatch != null && weakMatch.Groups.Count > 1 && weakMatch.Groups[1].Length > 0)
                {
                    Capture classNameCapture = weakMatch.Groups[1];

                    actualType.UnderlyingType = classNameCapture.Value;
                    actualType.ParameterType = string.Format("{0}*", classNameCapture.Value);
                    actualType.FieldType = actualType.ParameterType;
                }
                else if (!TypeRegistry.IsValueType(definitionType))
                {
                    actualType.ParameterType = string.Format("std::shared_ptr<{0}>", actualType.ParameterType);
                    actualType.FieldType = string.Format("std::shared_ptr<{0}>", actualType.FieldType);
                }
            }

            if (actualType.UnderlyingType == null)
		    	actualType.UnderlyingType = definitionType;

			return actualType;
		}

		private void Generate(string templatePath, string outputPath, PlatformModel platform, GenerationOptions options = GenerationOptions.None)
		{
			if (templatePath == null)
				throw new ArgumentNullException("templatePath");
			if (outputPath == null)
				throw new ArgumentNullException("outputPath");

			m_textHost.CurrentInterface = null;
			m_textHost.CurrentPlatform = platform;

			m_textHost.TemplateFile = ResolveTemplatePath(templatePath);
			string templateText = GetTemplateText(m_textHost.TemplateFile);

            DateTime lastUpdated = File.Exists(outputPath) ? File.GetLastWriteTimeUtc(outputPath) : DateTime.MinValue;
            if (!File.Exists(outputPath) || (options.HasFlag(GenerationOptions.AllowOverwrite) && DateTime.Compare(lastUpdated, platform.Parent.UpdatedAt) < 0))
                GenerateFile(outputPath, templateText);
		}

		private void Generate(string templatePath, string outputPath, InterfaceModel model, GenerationOptions options = GenerationOptions.None)
		{
			if (templatePath == null)
				throw new ArgumentNullException("templatePath");
			if (outputPath == null)
				throw new ArgumentNullException("outputPath");

			m_textHost.CurrentInterface = model;
			m_textHost.CurrentPlatform = null;

			m_textHost.TemplateFile = ResolveTemplatePath(templatePath);
			string templateText = GetTemplateText(m_textHost.TemplateFile);

            DateTime lastUpdated = File.Exists(outputPath) ? File.GetLastWriteTimeUtc(outputPath) : DateTime.MinValue;
            if (!File.Exists(outputPath) || (options.HasFlag(GenerationOptions.AllowOverwrite) && DateTime.Compare(lastUpdated, model.UpdatedAt) < 0))
			    GenerateFile(outputPath, templateText);
		}

		private string GetTemplateText(string templatePath)
		{
			if (templatePath == null)
				throw new ArgumentNullException("templatePath");

			string templateText = File.ReadAllText(templatePath, Encoding.UTF8);
			if (string.IsNullOrEmpty(templateText))
			{
				Console.Error.WriteLine("Unable to load template \"{0}\".", templatePath);
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
                string outputDirectory = Path.GetDirectoryName(filePath);
                if (!Directory.Exists(outputDirectory))
                    Directory.CreateDirectory(outputDirectory);

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
						Console.Error.WriteLine("Unable to locate template path \"{0}\".", templatePath);
						templatePathFull = null;
					}
				}
			}

			return templatePathFull;
		}

		private static readonly Dictionary<string, TypeModel> s_definitionsToCppTypes = new Dictionary<string, TypeModel>()
		{
			{ "string", new TypeModel { ParameterType = "const std::string&", FieldType = "std::string" } }
		};

        private static readonly Regex s_rgWeakReference = new Regex("weak<(\\w+)>");

		private readonly Engine m_textEngine;
		private readonly CPlusPlusTemplateHost m_textHost;

		public string OutputPath { get; set; }

	}
}
