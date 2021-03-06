﻿using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TextTemplating;

namespace TalonGenerate
{
	internal class WrapperTemplateHost : ITextTemplatingEngineHost
	{
		public IList<string> StandardAssemblyReferences
		{
			get
			{
				return new[]
				{
					// mscorlib
					typeof(Uri).Assembly.Location,
					// System.Core
					typeof(Enumerable).Assembly.Location,
					// Mono.TextTemplating
					typeof(Engine).Assembly.Location,
					// This assembly
					typeof(WrapperTemplateHost).Assembly.Location
				};
			}
		}

		public IList<string> StandardImports
		{
			get { return new[] { "System", "TalonGenerate", "System.Linq", "System.Collections.Generic" }; }
		}

		public string TemplateFile { get; internal set; }
		public TypeModel Model { get; internal set; }
		public List<TypeModel> AllModels { get; set; }

		public WrapperTemplateHost()
		{
		}

		public object GetHostOption(string optionName)
		{
			object returnObject = null;
			switch (optionName)
			{
			case "CacheAssemblies":
				returnObject = true;
				break;
			case "Model":
				returnObject = Model;
				break;
			case "AllModels":
				returnObject = AllModels;
				break;
			}
			return returnObject;
		}

		public bool LoadIncludeText(string requestFileName, out string content, out string location)
		{
			content = String.Empty;
			location = String.Empty;

			// TODO: Support Embedded Resources

			if (File.Exists(requestFileName))
			{
				content = File.ReadAllText(requestFileName);
				location = requestFileName;
				return true;
			}

			string templatePath = Path.Combine("Templates", requestFileName);
			if (File.Exists(templatePath))
			{
				content = File.ReadAllText(templatePath);
				location = templatePath;
				return true;
			}

			return false;
		}

		public AppDomain ProvideTemplatingAppDomain(string content)
		{
			return null;
		}

		public string ResolveAssemblyReference(string assemblyReference)
		{
			if (File.Exists(assemblyReference))
				return assemblyReference;

			string candidate = Path.Combine(Path.GetDirectoryName(TemplateFile), assemblyReference);
			if (File.Exists(candidate))
				return candidate;

			return "";
		}

		public Type ResolveDirectiveProcessor(string processorName)
		{
			throw new Exception("Directive Processor not found");
		}

		public string ResolveParameterValue(string directiveId, string processorName, string parameterName)
		{
			if (directiveId == null)
				throw new ArgumentNullException("directiveId");
			if (processorName == null)
				throw new ArgumentNullException("processorName");
			if (parameterName == null)
				throw new ArgumentNullException("parameterName");

			return String.Empty;
		}

		public string ResolvePath(string path)
		{
			if (path == null)
				throw new ArgumentNullException("path");

			if (File.Exists(path))
				return path;

			string candidate = Path.Combine(Path.GetDirectoryName(TemplateFile), path);
			if (File.Exists(candidate))
				return candidate;

			return path;
		}

		public void SetFileExtension(string extension)
		{
			m_defaultFileExtension = extension;
		}

		public void SetOutputEncoding(Encoding encoding, bool fromOutputDirective)
		{
			m_fileEncoding = encoding;
		}

		public void LogErrors(CompilerErrorCollection errors)
		{
			if (errors != null && errors.Count > 0)
			{
				foreach (CompilerError error in errors)
				{
					//C:\Users\mrudder\Projects\Talon\tools\TalonGenerate\WrapperTemplateHost.cs(153,6,153,7): error CS1056: Unexpected character '\'

					Console.WriteLine("{0}({1},{2}): {3} {4}: {5}", error.FileName, error.Line, error.Column, error.IsWarning ? "warn" : "error", error.ErrorNumber,  error.ErrorText);
				}
			}
		}

		private string m_defaultFileExtension;
		private Encoding m_fileEncoding;
	}
}
