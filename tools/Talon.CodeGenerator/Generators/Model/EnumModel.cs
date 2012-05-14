using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Talon.CodeGenerator.Generators.Model;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class EnumModel
	{
		public string Name { get; set; }
		public string Module { get; set; }
		public IList<EnumValueModel> Values { get; set; }
		public DateTime UpdatedAt { get; set; }

		public string FullyQualifiedName
		{
			get
			{
				return string.Format("{0}.{1}", Module, Name);
			}
		}
	}
}
