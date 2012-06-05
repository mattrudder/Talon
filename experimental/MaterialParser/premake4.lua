-- 
-- Material parser
--
project "MaterialParser"
    uuid        "1F796E28-AF57-11E1-86F6-D9106188709B"
	targetname  "MaterialParser"
	language    "C++"
	kind        "ConsoleApp"
	flags       { "FatalWarnings" }

    includedirs {
        "./"
    }

	files {
		"**.cpp"
	}
