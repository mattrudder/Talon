using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class FieldModel
	{
		public string Name { get; set; }
		public TypeModel Type { get; set; }
	}
}
