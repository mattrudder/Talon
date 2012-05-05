using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Talon.CodeGenerator.Generators.Model
{
	[Flags]
	public enum ParameterListOptions
	{
		None = 0,
		IncludeNames = 1,
		IncludeTypes = 2,
		IncludeAll = 3
	}
}
