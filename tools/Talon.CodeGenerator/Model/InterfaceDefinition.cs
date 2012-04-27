using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator
{
	public sealed class InterfaceDefinition : SymbolDefinition
	{
		public IList<MethodDefinition> Delegates { get; set; }
		public IList<MethodDefinition> Methods { get; set; }
		public IList<PropertyDefinition> Properties { get; set; }
	}
}
