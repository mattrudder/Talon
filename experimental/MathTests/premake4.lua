-- 
-- Math tests
--

project "MathTests"
    uuid        "1A11C869-7EA7-4CEC-BBD2-148150E7B500"
	targetname  "MathTests"
	language    "C++"
	kind        "ConsoleApp"
	--flags       { "FatalWarnings" }

    includedirs {
        "../../build",
        "./",
        "../../include/",
		"../../externals/nowide"
    }

	files {
		"**.cpp",
		"**.h",
		"../../src/Talon/TalonAssert.cpp",
		"../../include/Talon/Talon*.h",
		"../../include/Talon/Math/*.h",
        "../../include/Talon/Math/*.inl",
        "../../include/Talon/Math/SSE/*.h",
        "../../include/Talon/Math/SSE/*.inl"
	}

