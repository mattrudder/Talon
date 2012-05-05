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

		public static InterfaceModel GetType(string typeName)
		{
			InterfaceModel returnModel = null;
			s_interfaceMap.TryGetValue(typeName, out returnModel);
			return returnModel;
		}

		internal static void RegisterType(InterfaceModel model)
		{
			s_interfaceMap[model.FullyQualifiedName] = model;
		}

		internal static void ForEachType(Action<InterfaceModel> fnEach)
		{
			s_interfaceMap.ForEach(kv => fnEach(kv.Value));
		}

		private static readonly Dictionary<string, InterfaceModel> s_interfaceMap = new Dictionary<string, InterfaceModel>();
		private static readonly string[] s_valueTypes = new[]
		{
			"void", "int", "short", "long", "float", "double", "string"
		};
	}
}
