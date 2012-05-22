using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AutoMapper;
using Talon.CodeGenerator.Generators.Model;
using Talon.CodeGenerator.Parsing.Model;
using System.Collections.ObjectModel;

namespace Talon.CodeGenerator
{
	public static class TypeRegistry
	{
		public static int Count
		{
			get { return s_typeMap.Count; }
		}

		public static bool IsValueType(string typeName)
		{
			ITypeModel typeModel = GetType(typeName);
			return typeModel is EnumModel || typeName.Trim().EndsWith("*") || s_valueTypes.Contains(typeName, StringComparer.InvariantCultureIgnoreCase);
		}

		public static bool IsGeneratedType(string typeName)
		{
			return s_typeMap.Any(kv => string.Equals(kv.Key, typeName, StringComparison.InvariantCultureIgnoreCase));
		}

		public static InterfaceModel GetInterface(string typeName)
		{
			return GetType(typeName) as InterfaceModel;
		}

		public static EnumModel GetEnum(string typeName)
		{
			return GetType(typeName) as EnumModel;
		}

		public static ITypeModel GetType(string typeName)
		{
			ITypeModel returnModel = null;
			s_typeMap.TryGetValue(typeName, out returnModel);
			return returnModel;
		}

		internal static void RegisterType(ITypeModel model)
		{
			s_typeMap[model.Name] = model;
		}

		internal static void ForEachType(Action<ITypeModel> fnEach)
		{
			s_typeMap.ForEach(kv => fnEach(kv.Value));
		}

		private static readonly Dictionary<string, ITypeModel> s_typeMap = new Dictionary<string, ITypeModel>();
	
		private static readonly string[] s_valueTypes = new[]
		{
			"void", "bool", "int", "short", "long", "float", "double", "string"
		};
	}
}
