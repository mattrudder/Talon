using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Parsing.Model
{
	public sealed class EnumDefinition : SymbolDefinition
	{
		public IList<EnumValueDefinition> Values { get; set; }
	}
}
