using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator
{
	public sealed class DefinitionModule
	{
		public string Module { get; set; }
		public IList<InterfaceDefinition> Interfaces { get; set; }
	}
}
