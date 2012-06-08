-- 
-- Material parser
--

local antlrPath = get_absolute_from_solution("tools/Antlr/antlr-3.4-complete-no-antlrv2.jar")
local generatedPath = path.getabsolute("src/generated")
local grammarPath = path.getabsolute("src/TalonMaterial.g")
local antlrCommand = "java -cp " .. antlrPath .. " org.antlr.Tool -o " .. generatedPath .. " " .. grammarPath

if not os.isdir(generatedPath) then
	os.mkdir(generatedPath)
end

os.outputof(antlrCommand)

project "MaterialParser"
    uuid        "1F796E28-AF57-11E1-86F6-D9106188709B"
	targetname  "MaterialParser"
	language    "C++"
	kind        "ConsoleApp"
	--flags       { "FatalWarnings" }

    includedirs {
        "./"
    }

	files {
		"**.cpp",
		"**.c",
		"**.h",
		"**.mat"
	}

	prebuildcommands {
		antlrCommand
	}

    postbuildcommands {
        copy_cmd("src/test.mat")
    }

	apply_external("libantlr3c-3.4", "antlr3c", true)
