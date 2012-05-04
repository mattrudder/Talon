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

		public void GenerateParameterList(dynamic templateClass, bool includeNames = true)
		{
			int i = 0;
			foreach (ParameterModel param in Parameters)
			{
				if (i > 0)
					templateClass.Write(", ");

				if (includeNames)
					templateClass.Write(string.Format("{0} {1}", param.Type.ParameterType, param.Name));
				else
					templateClass.Write(param.Type.ParameterType);

				++i;
			}
		}
	}
}
