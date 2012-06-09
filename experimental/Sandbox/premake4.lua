-- 
-- Test App
--
project "Sandbox"
    uuid        "16D42CD3-C21B-CD4B-9CB1-614FFAD9349F"
	targetname  "TalonSandbox"
	language    "C++"
	kind        "WindowedApp"
	flags       { "FatalWarnings", "WinMain" }
	links		{ "Talon" }

    includedirs {
        "./"
    }

	files {
		"./*.cpp",
        "./*.h"
	}

    configuration "MacOSX"
        files {
            "Mac/**"
        }

    configuration "Windows"
        postbuildcommands {
            copy_cmd("test.png")
        }