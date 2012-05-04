using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Talon.CodeGenerator.Parsing.Model;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class InterfaceModel
	{
		public string Name { get; set; }
		public string Module { get; set; }
		public IList<PlatformModel> Platforms { get; set; }
		public IList<MethodModel> Methods { get; set; }
		public IList<PropertyModel> Properties { get; set; }
		public IList<MethodModel> Delegates { get; set; }

		public IEnumerable<TypeModel> GetReferencedTypes()
		{
			return GetReferencedTypesCore().Distinct().OrderBy(t => t.FieldType);
		}

		private IEnumerable<TypeModel> GetReferencedTypesCore()
		{
			foreach (MethodModel method in Methods)
				yield return method.ReturnType;

			foreach (MethodModel method in Delegates)
				yield return method.ReturnType;

			foreach (PropertyModel property in Properties)
				yield return property.Type;
		}
	}
}
