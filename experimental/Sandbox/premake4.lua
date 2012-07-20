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

    local copyCommands = copy_cmd("Resources/*", "Resources")
    copyCommands = copyCommands .. copy_cmd("*.png")

    -- Configuration
    configuration {}
        postbuildcommands { copyCommands }

    configuration "MacOSX"
        files {
            "Mac/**"
        }
        linkoptions { "-stdlib=libc++" }