---
--- Premake build script for Talon Game Tech
---

dofile("scripts/utils.lua")

local localHostName = os.getenv("COMPUTERNAME")

if not _OPTIONS["to"] then
    if _ACTION then
		_OPTIONS["to"] = "build/" .. _ACTION
    else
		_OPTIONS["to"] = "build"
    end
end

if not _OPTIONS["gfx"] then     
    if os.is("windows") then
		_OPTIONS["gfx"] = "Direct3D11"
    else
		_OPTIONS["gfx"] = "OpenGL"
    end
end

if isgeneratoraction(_ACTION) then
    printf("Talon Engine projects at %s using:", _OPTIONS["to"])
    printf(" - Host System: %s", localHostName)
    printf(" - Graphics: %s", _OPTIONS["gfx"])
end

if not _OPTIONS["scripts"] then
	_OPTIONS["scripts"] = "Scripts"
end


checkdirs {
	"bin/x86/Debug",
	"bin/x86/Release"
}

solution "Talon"
	location(_OPTIONS["to"])
	configurations	{ "Release", "Debug" }
	defines 		{ string.format("HOST_%s", string.upper(localHostName)) }
	flags       	{ "EnableSSE2", "ExtraWarnings", "FloatFast", "Unicode" }
	includedirs		{ "include" }

    configuration "Debug"
        defines "_DEBUG"
        flags { "Symbols" }
        targetdir "bin/x86/Debug"
        
    configuration "Release"
        defines "NDEBUG"
        flags { "OptimizeSpeed" }
        targetdir "bin/x86/Release"

	-- 
	-- Library
	-- 
	project "Talon"
		targetname  "Talon"
		language    "C++"
		kind        "SharedLib"
		defines     { "ZLIB_DLL", "ZLIB_WINAPI","TALON_DLL", "BUILDING_TALON" }
		flags       { "FatalWarnings" }
		links		{ "nowide", "glew" }

		pchheader	"TalonPrefix.h"
		pchsource	"src/Talon/TalonPrefix.cpp"

		files {
			"include/Talon/*.h",
			"include/Talon/Graphics/*.h",
			"include/Talon/Platform/*.h",

			"src/Talon/TalonPrefix.h",
			"src/Talon/*.cpp",
			"src/Talon/Graphics/*.cpp",
			"src/Talon/Platform/*.cpp"
		}

		includedirs {
			"build",
			"src/Talon",
			"externals/nowide",
			"externals/zlib-1.2.6/include",
			"externals/libpng-1.5.10/include",
			"externals/cairo-1.8.8/include",
			"externals/glew-1.7.0/include"
		}

		-- Configuration
		configuration "Release"
			flags { "OptimizeSpeed" }

	-- 
	-- Client Applications
	--
	project "Sandbox"
		targetname  "TalonSandbox"
		language    "C++"
		kind        "WindowedApp"
		flags       { "FatalWarnings" }
		links		{ "Talon" }

		files {
			"src/Sandbox/*.cpp"
		}

	--
	-- dependencies
	--
	project "nowide"
		language "C++"
		kind "StaticLib"

		includedirs { "externals/nowide" }
		files {
			"externals/nowide/**.cpp"
		}

	project "glew"
		language "C++"
		kind "StaticLib"
		defines "GLEW_BUILD"

		includedirs { "externals/glew-1.7.0/include" }
		files {
			"externals/glew-1.7.0/src/glew.c"
		}

if _ACTION == "clean" then
	os.rmdir("bin")
	os.rmdir("build")
end

newoption {
	trigger = "to",
	value   = "path",
	description = "Set the output location for the generated files"
}

newoption {
    trigger = "gfx",
    value   = "api",
    description = "Sets the graphics API to use",
    allowed = {
        { "OpenGL",    "OpenGL" },
        { "Direct3D11",  "Direct3D 11 (Windows only)" },
    },
    optional = true 
}