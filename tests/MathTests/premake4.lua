-- 
-- Math tests
--

project "MathTests"
    uuid        "1A11C869-7EA7-4CEC-BBD2-148150E7B500"
	targetname  "MathTests"
	language    "C++"
	kind        "ConsoleApp"
	flags       { "FatalWarnings" }
	links		{ "Talon", "UnitTest++" }

    includedirs {
        "./",
    }

	files {
		"./*.cpp",
        "./*.h"
	}
