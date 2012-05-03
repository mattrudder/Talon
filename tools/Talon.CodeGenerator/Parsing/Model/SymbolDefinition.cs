using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Parsing.Model
{
	public abstract class SymbolDefinition
	{
        public string OuterScope { get; set; }
		public string Name { get; set; }
	}
}
