using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Talon.CodeGenerator.Parsing.Model;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class InterfaceModel : ITypeModel
	{
		public string Name { get; set; }
		public string Module { get; set; }

		public IList<PlatformModel> Platforms { get; set; }
		public IList<MethodModel> Constructors { get; set; }
		public IList<MethodModel> Methods { get; set; }
		public IList<PropertyModel> Properties { get; set; }
		public IList<MethodModel> Delegates { get; set; }
		public IList<FieldModel> Fields { get; set; }
        public DateTime UpdatedAt { get; set; }

		public string FullyQualifiedName
		{
			get
			{
				return string.Format("{0}.{1}", Module, Name);
			}
		}

		public PropertyModel GetProperty(string propertyName)
		{
			return Properties.FirstOrDefault(p => string.Equals(p.Name, propertyName, StringComparison.InvariantCultureIgnoreCase));
		}

		public FieldModel GetField(string fieldName)
		{
			return Fields.FirstOrDefault(f => string.Equals(f.Name, fieldName, StringComparison.InvariantCultureIgnoreCase));
		}

		public IEnumerable<ReferencedType> GetReferencedTypes()
		{
			return GetReferencedTypesCore().Distinct().Where(t => t != null && t.UnderlyingType != null).OrderBy(t => t.UnderlyingType);
		}

		private IEnumerable<ReferencedType> GetReferencedTypesCore()
		{
			foreach (ReferencedType type in Constructors.SelectMany(c => c.Parameters.Select(p => p.Type)))
				yield return type;

			foreach (MethodModel method in Methods)
			{
				yield return method.ReturnType;
				foreach (var parameter in method.Parameters)
					yield return parameter.Type;
			}

			foreach (MethodModel method in Delegates)
			{
				yield return method.ReturnType;
				foreach (var parameter in method.Parameters)
					yield return parameter.Type;
			}

			foreach (PropertyModel property in Properties)
				yield return property.Type;
		}
    }
}
