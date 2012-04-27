using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator
{
	public sealed class ModuleSettings
	{
		public string Name { get; set; }
		public IList<PlatformSettings> Platforms { get; set; }
	}
}
