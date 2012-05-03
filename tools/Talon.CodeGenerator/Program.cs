using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Talon.CodeGenerator
{
    public static class EnumerableUtility
    {
        public static void ForEach<T>(this IEnumerable<T> enumerable, Action<T> fnEach)
        {
            foreach (T item in enumerable)
                fnEach(item);
        }
    }

	class Program
	{
        static private void LogSymbol(string symbolName)
        {
            Console.WriteLine("{0}", symbolName);
        }

        static private void PropagateOuterScope(DefinitionModule module)
        {
            module.Interfaces.ForEach(i =>
            {
                string interfaceName = string.Format("{0}.{1}", module.Module, i.Name);
                i.OuterScope = module.Module;

                LogSymbol(interfaceName);

                i.Methods.ForEach(m =>
                {
                    string methodScope = string.Format("{0}.{1}", interfaceName, m.Name);
                    m.OuterScope = interfaceName;
                    m.Parameters.ForEach(p => p.OuterScope = methodScope);

                    LogSymbol(methodScope);
                });

                i.Delegates.ForEach(d =>
                {
                    string delegateScope = string.Format("{0}.{1}", interfaceName, d.Name);
                    d.OuterScope = interfaceName;
                    d.Parameters.ForEach(p => p.OuterScope = delegateScope);

                    LogSymbol(delegateScope);
                });

                i.Properties.ForEach(p => p.OuterScope = interfaceName);
            });
        }

        static private void ProcessDefinitions(string path)
        {
            if (path == null)
                throw new ArgumentNullException("path");
            if (!Directory.Exists(path))
                throw new ArgumentException("path does not exist.");

            string[] definitionFiles = Directory.GetFiles(path, "*.json", SearchOption.AllDirectories);
            foreach (string definitionFile in definitionFiles)
            {
                DefinitionModule module = null;
                using (TextReader tw = new StreamReader(definitionFile))
                {
                    string file = tw.ReadToEnd();
                    module = JsonConvert.DeserializeObject<DefinitionModule>(file);

                    PropagateOuterScope(module);
                }
            }

            Console.WriteLine("Press enter to quit.");
            Console.ReadLine();
        }

		static void Main(string[] args)
		{
			using (TextReader tw = new StreamReader("Settings.json"))
			{
				string file = tw.ReadToEnd();
				s_settings = JsonConvert.DeserializeObject<CodeGeneratorSettings>(file);
			}

            // TODO: Take definition path as commandline options.
            ProcessDefinitions(Path.Combine(Directory.GetCurrentDirectory(), "Definitions"));
		}

		private static CodeGeneratorSettings s_settings;
	}
}
