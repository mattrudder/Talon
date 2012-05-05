using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Parsing.Model
{
	public class InterfaceDefinition : SymbolDefinition
	{
		public IList<MethodDefinition> Constructors { get; set; }
		public IList<MethodDefinition> Delegates { get; set; }
		public IList<MethodDefinition> Methods { get; set; }
		public IList<PropertyDefinition> Properties { get; set; }
	}
}
