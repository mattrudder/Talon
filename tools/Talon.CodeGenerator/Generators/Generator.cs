using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using Talon.CodeGenerator.Generators.Model;
using Talon.CodeGenerator.Parsing.Model;

namespace Talon.CodeGenerator.Generators
{
	public abstract class Generator
	{
		public abstract CodeGeneratorSettings Settings { get; set; }
		public int InterfaceCount { get; private set; }
		public int EnumCount { get; private set; }
		public int FileCount { get; protected set; }

		public void Generate(ITypeModel definition)
		{
			InterfaceModel interfaceModel = definition as InterfaceModel;
			if (interfaceModel != null)
			{
				++InterfaceCount;
				Generate(interfaceModel);
				return;
			}

			EnumModel enumModel = definition as EnumModel;
			if (enumModel != null)
			{
				++EnumCount;
				Generate(enumModel);
				return;
			}
		}

		protected void OutputFile(string filePath, string outputText)
		{
			if (filePath == null)
				throw new ArgumentNullException("filePath");
			if (outputText == null)
				throw new ArgumentNullException("outputText");

			string outputDirectory = Path.GetDirectoryName(filePath);
			if (!Directory.Exists(outputDirectory))
				Directory.CreateDirectory(outputDirectory);

			using (TextWriter tw = new StreamWriter(filePath))
			{
				tw.Write(outputText);
				++FileCount;
			}
		}

		protected abstract void Generate(InterfaceModel definition);
		protected abstract void Generate(EnumModel definition);
	}
}
