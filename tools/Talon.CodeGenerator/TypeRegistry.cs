using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using Talon.CodeGenerator.Generators.Model;
using Talon.CodeGenerator.Parsing.Model;

namespace Talon.CodeGenerator
{
	public static class TypeRegistry
	{
		public static bool IsValueType(string typeName)
		{
			return s_valueTypes.Contains(typeName, StringComparer.InvariantCultureIgnoreCase);
		}

		private static readonly string[] s_valueTypes = new[]
		{
			"void", "int", "short", "long", "float", "double", "string"
		};
	}
}
