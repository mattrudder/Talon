using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Talon.CodeGenerator
{
	class Program
	{
		static void Main(string[] args)
		{
			using (TextReader tw = new StreamReader("Settings.json"))
			{
				string file = tw.ReadToEnd();
				s_settings = JsonConvert.DeserializeObject<CodeGeneratorSettings>(file);
			}

			DefinitionModule module = null;
			using (TextReader tw = new StreamReader("Window.json"))
			{
				string file = tw.ReadToEnd();
				module = JsonConvert.DeserializeObject<DefinitionModule>(file);
			}

			foreach (var iface in module.Interfaces)
			{
				Console.WriteLine("TODO: Generating files for {0}", iface.Name);
			}
		}

		static 

		private static CodeGeneratorSettings s_settings;
	}
}
