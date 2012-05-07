using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class PlatformModel
	{
		public string Name { get; set; }
		public string ShortName { get; set; }
		public string Condition { get; set; }
        public string CPlusPlusExtension { get; set; }
		public InterfaceModel Parent { get; set; }

		public string ClassName
		{
			get
			{
				if (m_className == null)
					m_className = string.Format("{0}{1}", ShortName, Parent.Name);

				return m_className;
			}
		}

		private string m_className;
    }
}
