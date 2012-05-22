using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Generators.Model
{
	public interface ITypeModel
	{
		string Name { get; set; }
		string Module { get; set; }
		DateTime UpdatedAt { get; set; }
	}
}
