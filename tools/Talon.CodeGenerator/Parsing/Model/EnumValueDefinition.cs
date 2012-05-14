using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Parsing.Model
{
	public sealed class EnumValueDefinition : SymbolDefinition
	{
		public string Value { get; set; }
	}
}
