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
	internal interface IGenerator
	{
		string OutputPath { get; set; }

        void Generate(InterfaceModel definition);
	}
}
