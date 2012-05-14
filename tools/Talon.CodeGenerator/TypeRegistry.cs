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
			return s_valueTypes.Contains(typeName, StringComparer.InvariantCultureIgnoreCase) || s_enumMap.Any(kv => string.Equals(kv.Key, typeName, StringComparison.InvariantCultureIgnoreCase));
		}

		public static InterfaceModel GetInterface(string typeName)
		{
			InterfaceModel returnModel = null;
			s_interfaceMap.TryGetValue(typeName, out returnModel);
			return returnModel;
		}

		internal static void RegisterInterface(InterfaceModel model)
		{
			s_interfaceMap[model.Name] = model;
		}

		internal static void ForEachInterface(Action<InterfaceModel> fnEach)
		{
			s_interfaceMap.ForEach(kv => fnEach(kv.Value));
		}

		internal static void RegisterEnum(EnumModel model)
		{
			s_enumMap[model.Name] = model;
		}

		internal static void ForEachEnum(Action<EnumModel> fnEach)
		{
			s_enumMap.ForEach(kv => fnEach(kv.Value));
		}

		private static readonly Dictionary<string, InterfaceModel> s_interfaceMap = new Dictionary<string, InterfaceModel>();
		private static readonly Dictionary<string, EnumModel> s_enumMap = new Dictionary<string, EnumModel>();

		private static readonly string[] s_valueTypes = new[]
		{
			"void", "bool", "int", "short", "long", "float", "double", "string"
		};
	}
}
