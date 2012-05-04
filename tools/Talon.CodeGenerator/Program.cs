using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Talon.CodeGenerator.Generators.Model;
using Talon.CodeGenerator.Parsing.Model;
using Talon.CodeGenerator.Generators;
using Talon.CodeGenerator.Generators.CPlusPlus;
using AutoMapper;

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
					foreach (var iface in module.Interfaces)
					{
						InterfaceModel model = CreateInterfaceModel(module.Module, iface);
						Console.WriteLine("Generating {0}...", model.Name);
						s_generator.Generate(model);
					}
                }
            }

            Console.WriteLine("Press enter to quit.");
            Console.ReadLine();
        }

		private static InterfaceModel CreateInterfaceModel(string module, InterfaceDefinition iface)
		{
			IList<PlatformSettings> platforms;
			if (!s_platformsForModule.TryGetValue(module, out platforms))
				return null;

			InterfaceModel model = Mapper.Map<InterfaceDefinition, InterfaceModel>(iface);
			model.Module = module;
			model.Platforms = new List<PlatformModel>();
			foreach (PlatformSettings platform in platforms)
			{
				model.Platforms.Add(new PlatformModel
				{
					Name = platform.Name,
					ShortName = platform.ShortName,
					Condition = platform.Condition,
					Parent = model
				});
			}

			return model;
		}

		static void Main(string[] args)
		{
			using (TextReader tw = new StreamReader("bin/Debug/Settings.json"))
			{
				string file = tw.ReadToEnd();
				s_settings = JsonConvert.DeserializeObject<CodeGeneratorSettings>(file);

				s_platformsForModule = s_settings.Modules.ToDictionary(m => m.Name, m => m.Platforms, StringComparer.InvariantCultureIgnoreCase);
			}

            // TODO: Take definition path as command line options.
			s_generator = new CPlusPlusGenerator
			{
				OutputPath = Path.Combine(Directory.GetCurrentDirectory(), "include/Talon")
			};
			SetupMappers();

            ProcessDefinitions(Path.Combine(Directory.GetCurrentDirectory(), "bin/Debug/Definitions"));
		}

		private static void SetupMappers()
		{
			Mapper.CreateMap<InterfaceDefinition, InterfaceModel>();
			Mapper.CreateMap<MethodDefinition, MethodModel>();
			Mapper.CreateMap<ParameterDefinition, ParameterModel>();
			Mapper.CreateMap<PropertyDefinition, PropertyModel>();
		}

		private static CodeGeneratorSettings s_settings;
		private static Dictionary<string, IList<PlatformSettings>> s_platformsForModule;
		private static IGenerator s_generator;
	}
}
