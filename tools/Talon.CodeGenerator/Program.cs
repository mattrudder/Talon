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
using System.Reflection;

namespace Talon.CodeGenerator
{
    public static class EnumerableUtility
    {
        public static void ForEach<T>(this IEnumerable<T> enumerable, Action<T> fnEach)
        {
			if (enumerable == null)
				return;

            foreach (T item in enumerable)
                fnEach(item);
        }
    }

	class Program
	{
		static private void ProcessModule(DefinitionModule module)
        {
            module.Interfaces.ForEach(i =>
            {
                string interfaceName = string.Format("{0}.{1}", module.Module, i.Name);
                i.OuterScope = module.Module;

				i.Constructors.ForEach(m =>
				{
					m.Name = i.Name;

					string methodScope = string.Format("{0}.{1}", interfaceName, m.Name);
					m.OuterScope = interfaceName;
					m.Parameters.ForEach(p => p.OuterScope = methodScope);
				});

                i.Methods.ForEach(m =>
                {
                    string methodScope = string.Format("{0}.{1}", interfaceName, m.Name);
                    m.OuterScope = interfaceName;
                    m.Parameters.ForEach(p => p.OuterScope = methodScope);
                });

                i.Delegates.ForEach(d =>
                {
                    string delegateScope = string.Format("{0}.{1}", interfaceName, d.Name);
                    d.OuterScope = interfaceName;
                    d.Parameters.ForEach(p => p.OuterScope = delegateScope);
                });

                i.Properties.ForEach(p => p.OuterScope = interfaceName);
				i.Fields.ForEach(f => f.OuterScope = interfaceName);
            });

			module.Enums.ForEach(e =>
			{
				e.OuterScope = module.Module;

				string enumName = string.Format("{0}.{1}", module.Module, e.Name);
				e.Values.ForEach(v => v.OuterScope = enumName);
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
                DateTime lastUpdated = File.GetLastWriteTimeUtc(definitionFile);
                DefinitionModule module = null;
                using (TextReader tw = new StreamReader(definitionFile))
                {
                    string file = tw.ReadToEnd();
                    module = JsonConvert.DeserializeObject<DefinitionModule>(file);

                    ProcessModule(module);

					// Register all generated types before generation, so templates can access other types.
					module.Interfaces.ForEach(i =>
					{
						InterfaceModel model = CreateInterfaceModel(module.Module, i);
                        model.UpdatedAt = lastUpdated;
						TypeRegistry.RegisterType(model);
					});

					module.Enums.ForEach(e =>
					{
						EnumModel model = CreateEnumModel(module.Module, e);
						model.UpdatedAt = lastUpdated;
						TypeRegistry.RegisterType(model);
					});
                }
            }

			// Generate
			s_generator.Settings = s_settings;
			TypeRegistry.ForEachType(i => s_generator.Generate(i));
        }

		private static EnumModel CreateEnumModel(string module, EnumDefinition e)
		{
			EnumModel model = Mapper.Map<EnumDefinition, EnumModel>(e);
			model.Module = module;

			return model;
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
                    CPlusPlusExtension = platform.CPlusPlusExtension,
					Parent = model
				});
			}

			return model;
		}

		static void Main(string[] args)
		{
            string workingPath = Path.GetDirectoryName(Assembly.GetEntryAssembly().Location);
            using (TextReader tw = new StreamReader(Path.Combine(workingPath, "Settings.json")))
			{
				string file = tw.ReadToEnd();
				s_settings = JsonConvert.DeserializeObject<CodeGeneratorSettings>(file);

				s_platformsForModule = s_settings.Modules.ToDictionary(m => m.Name, m => m.Platforms, StringComparer.InvariantCultureIgnoreCase);
			}

            s_generator = new CPlusPlusGenerator
            {
				Settings = s_settings
            };
			
			s_settings.OutputPath = Path.Combine(workingPath, s_settings.OutputPath ?? "");
			s_settings.DefinitionsPath = Path.Combine(workingPath, s_settings.DefinitionsPath ?? "");

			SetupMappers();
			ProcessDefinitions(s_settings.DefinitionsPath);

			int typeCount = s_generator.InterfaceCount + s_generator.EnumCount;
			Console.WriteLine("Processed {0} types, generated {1} files.", typeCount, s_generator.FileCount);
		}

		private static void SetupMappers()
		{
			Mapper.CreateMap<InterfaceDefinition, InterfaceModel>();
			Mapper.CreateMap<MethodDefinition, MethodModel>();
			Mapper.CreateMap<ParameterDefinition, ParameterModel>();
			Mapper.CreateMap<PropertyDefinition, PropertyModel>();
			Mapper.CreateMap<FieldDefinition, FieldModel>();
			Mapper.CreateMap<EnumDefinition, EnumModel>();
			Mapper.CreateMap<EnumValueDefinition, EnumValueModel>();
		}

		private static CodeGeneratorSettings s_settings;
		private static Dictionary<string, IList<PlatformSettings>> s_platformsForModule;
		private static Generator s_generator;
	}
}
