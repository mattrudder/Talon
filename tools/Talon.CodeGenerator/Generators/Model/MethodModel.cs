using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Talon.CodeGenerator.Parsing.Model;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class MethodModel
	{
		public string Name { get; set; }
		public TypeModel ReturnType { get; set; }
		public IList<ParameterModel> Parameters { get; set; }

		public void GenerateParameterList(dynamic templateClass, ParameterListOptions options = ParameterListOptions.IncludeAll)
		{
			Func<TypeModel, string> whichType = p => p.ParameterType;
			GenerateParameterList(templateClass, whichType, options);
		}

		public void GenerateParameterList(dynamic templateClass, Func<TypeModel, string> whichType, ParameterListOptions options = ParameterListOptions.IncludeAll)
		{
			int i = 0;
			foreach (ParameterModel param in Parameters)
			{
				if (i > 0)
					templateClass.Write(", ");

				if (options.HasFlag(ParameterListOptions.IncludeTypes))
				{
					templateClass.Write(whichType(param.Type));
					if (options.HasFlag(ParameterListOptions.IncludeNames))
						templateClass.Write(" " + param.Name);
				}
				else if (options.HasFlag(ParameterListOptions.IncludeNames))
				{
					templateClass.Write(param.Name);
				}

				++i;
			}
		}
	}
}
