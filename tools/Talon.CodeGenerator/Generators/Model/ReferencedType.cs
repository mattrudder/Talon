﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Talon.CodeGenerator.Generators.Model
{
	public sealed class ReferencedType
	{
		public string UnderlyingType { get; set; }
		public string ParameterType { get; set; }
		public string FieldType { get; set; }
		public string DefaultValue { get; set; }

		public InterfaceModel Interface
		{
			get
			{
				if (m_interface == null)
					m_interface = TypeRegistry.GetInterface(UnderlyingType);

				return m_interface;
			}
		}

		InterfaceModel m_interface;
	}
}
