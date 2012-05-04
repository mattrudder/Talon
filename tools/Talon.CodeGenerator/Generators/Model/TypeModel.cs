using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class TypeModel
	{
		public string UnderlyingType { get; set; }
		public string ParameterType { get; set; }
		public string FieldType { get; set; }
	}
}
