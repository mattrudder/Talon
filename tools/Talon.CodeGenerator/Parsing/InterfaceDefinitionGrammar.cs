using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Irony.Parsing;

namespace Talon.CodeGenerator.Parsing
{
	[Language("Talon Interface Definition Language", "0.1", "Definition Language for Interfaces and Data used in Talon Engine")]
	public sealed class InterfaceDefinitionGrammar : Grammar
	{
		public InterfaceDefinitionGrammar()
		{
			/** Non-terminals */
			var DefinitionFile = new NonTerminal("DefinitionFile");
			var Statement = new NonTerminal("Statement");
			var ModuleStatement = new NonTerminal("Module");
			var InterfaceDefinition = new NonTerminal("InterfaceDefinition");

			Root = DefinitionFile;

			DefinitionFile.Rule = MakePlusRule(DefinitionFile, Statement);

			Statement.Rule = ModuleStatement | InterfaceDefinition;
		}
	}
}
