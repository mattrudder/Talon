using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Talon.CodeGenerator.Generators.CPlusPlus
{
    [Flags]
    public enum GenerationOptions
    {
        None = 0,
        AllowOverwrite = 1
    }
}
