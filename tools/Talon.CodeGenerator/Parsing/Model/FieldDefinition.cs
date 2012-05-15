using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Talon.CodeGenerator.Parsing.Model
{
	public sealed class FieldDefinition : SymbolDefinition
	{
		public string Type { get; set; }
	}
}
