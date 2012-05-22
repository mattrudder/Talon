using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Talon.CodeGenerator.Parsing.Model;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class PropertyModel
	{
		public string Name { get; set; }
		public ReferencedType Type { get; set; }
		public bool IsReadOnly { get; set; }
	}
}
