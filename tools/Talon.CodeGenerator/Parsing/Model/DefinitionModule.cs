using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Parsing.Model
{
	public sealed class DefinitionModule
	{
		public string Module { get; set; }
		public IList<InterfaceDefinition> Interfaces { get; set; }
		public IList<EnumDefinition> Enums { get; set; }
	}
}
