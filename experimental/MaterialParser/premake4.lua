-- 
-- Material parser
--
local bisonPath = "bison"
local flexPath = "flex"
local bisonSkelArgs = ""
local touchCmd = "touch"

local parserPath = path.getabsolute("src/generated/MaterialParser.cpp")
local lexerPath = path.getabsolute("src/generated/MaterialLexer.cpp")
local parserGrammarPath = path.getabsolute("MaterialParser.y")
local tokensPath = path.getabsolute("MaterialLexer.l")

if os.is("windows") then
	bisonPath = get_absolute_from_solution("tools/Win32/bison.exe")
	flexPath = get_absolute_from_solution("tools/Win32/flex.exe")
	touchCmd = "type nul >"
end

os.outputof(bisonPath .. " -d -o " .. parserPath .. bisonSkelArgs .. " " .. parserGrammarPath)
os.outputof(flexPath .. " -o" .. lexerPath .. " " .. tokensPath)

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
