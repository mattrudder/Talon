using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Parsing.Model
{
	public sealed class PropertyDefinition : SymbolDefinition
	{
		public string Type { get; set; }
		public bool IsReadOnly { get; set; }
	}
}
