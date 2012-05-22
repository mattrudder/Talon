using System;
using System.Collections.Generic;
using System.Data.Entity.Design.PluralizationServices;
using System.Globalization;
using System.Linq;
using System.Text;
using Talon.CodeGenerator.Generators.Model;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class EnumModel : ITypeModel
	{
		public string Name { get; set; }
		public string Module { get; set; }
		public IList<EnumValueModel> Values { get; set; }
		public DateTime UpdatedAt { get; set; }

		public string PluralName
		{
			get
			{
				return s_pluralService.Pluralize(Name);
			}
		}

		public string FullyQualifiedName
		{
			get
			{
				return string.Format("{0}.{1}", Module, Name);
			}
		}

		static private PluralizationService s_pluralService = PluralizationService.CreateService(CultureInfo.CurrentCulture);
	}
}
