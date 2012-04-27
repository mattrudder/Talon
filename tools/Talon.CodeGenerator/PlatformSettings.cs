using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator
{
	public sealed class PlatformSettings
	{
		public string Name { get; set; }
		public string ShortName { get; set; }
		public string Condition { get; set; }
	}
}