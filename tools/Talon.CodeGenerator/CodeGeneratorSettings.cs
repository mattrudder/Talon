using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator
{
	public sealed class CodeGeneratorSettings
	{
		public string OutputPath { get; set; }
		public string DefinitionsPath { get; set; }
		public bool ForceRegeneration { get; set; }
		public IList<ModuleSettings> Modules { get; set; }
	}
}
