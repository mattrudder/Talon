using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Parsing.Model
{
	public sealed class MethodDefinition : SymbolDefinition
	{
		public string ReturnType { get; set; }
		public IList<ParameterDefinition> Parameters { get; set; }
	}
}
