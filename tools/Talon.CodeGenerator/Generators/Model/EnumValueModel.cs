using System;
using System.Globalization;
using System.Collections.Generic;
using System.Data.Entity.Design.PluralizationServices;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class EnumValueModel
	{
		public string Name { get; set; }
		public string Module { get; set; }
		public string Value { get; set; }

		public string PluralName
		{
			get
			{
				return s_pluralService.Pluralize(Name);
			}
		}

		static private PluralizationService s_pluralService = PluralizationService.CreateService(CultureInfo.CurrentCulture);
	}
}
