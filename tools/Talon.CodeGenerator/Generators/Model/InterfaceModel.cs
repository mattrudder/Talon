using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Talon.CodeGenerator.Parsing.Model;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class InterfaceModel : InterfaceDefinition
	{
		public InterfaceModel(InterfaceDefinition definition)
		{
			this.Name = definition.Name;
			this.Methods = definition.Methods;
			this.Properties = definition.Properties;
			this.Delegates = definition.Delegates;
		}

		public string Module { get; set; }
		public List<PlatformModel> Platforms { get; set; }
	}
}
