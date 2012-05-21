---
--- Premake build script for Talon Game Tech
---

dofile("scripts/utils.lua")

local localHostName = os.getenv("COMPUTERNAME")
local codeGenPath = path.getabsolute("bin/Debug/Talon.CodeGenerator.exe")

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
    print("Talon Engine projects at " .. _OPTIONS["to"] .. " using:")
    print(" - Host System: " .. localHostName .. " (" .. string.format("HOST_%s", string.upper(string.gsub(localHostName, "[^%a%d]", "_"))) .. ")")
    print(" - Graphics: " .. _OPTIONS["gfx"])

    for k,v in pairs(_OPTIONS) do
        print(" - " .. k .. ": " .. v)
    end
end

if not _OPTIONS["scripts"] then
	_OPTIONS["scripts"] = "Scripts"
end

if not os.isfile(codeGenPath) then
    print "WARN: Code generator has not been built. Please build the project in tools/Talon.CodeGenerator."
else
    print "Processing definitions..."
    if os.is("windows") then
        os.execute(codeGenPath)
    else
        os.execute("mono " .. codeGenPath)
    end
end

makedirs {
	"bin/x86/Debug",
	"bin/x86/Release"
}

solution "Talon"
	location(_OPTIONS["to"])
	configurations	{ "Release", "Debug" }
	defines 		{ string.format("HOST_%s", string.upper(string.gsub(localHostName, "[^%a%d]", "_"))) }
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
        uuid        "67ED9308-E1BE-D947-AB41-04EC07B52663"
		targetname  "Talon"
		language    "C++"
		kind        "SharedLib"
		defines     { "ZLIB_DLL", "ZLIB_WINAPI","TALON_DLL", "BUILDING_TALON" }
		flags       { "FatalWarnings" }
		links		{ "nowide", "glew" }

		pchheader	"TalonPrefix.h"
		pchsource	"src/Talon/TalonPrefix.cpp"

		files {
            "definitions/**.json",

			"include/Talon/*.h",
			"include/Talon/Graphics/*.h",
            "include/Talon/Graphics/Base/*.h",
            "include/Talon/Graphics/Generated/*.h",
			"include/Talon/Platform/*.h",
            "include/Talon/Platform/Generated/*.h",

			"src/Talon/TalonPrefix.h",
			"src/Talon/*.cpp",
			"src/Talon/Graphics/*.cpp",
            "src/Talon/Graphics/Base/*.cpp",
			"src/Talon/Platform/*.cpp",
            "src/Talon/Platform/Base/*.cpp"
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

        -- Generic platform includes
        configuration "Windows"
            files {
                "include/Talon/Platform/Win32/**.h",
                "src/Talon/Platform/Win32/**.cpp"
            }

        configuration "MacOSX"
            files {
                "include/Talon/Platform/Mac/**.h",
                "src/Talon/Platform/Mac/**.cpp",
                "src/Talon/Platform/Mac/**.m",
                "src/Talon/Platform/Mac/**.mm"
            }

        configuration "OpenGL"
            defines { "GLEW_STATIC" }

        configuration { _OPTIONS["gfx"] }
            files {
                "include/Talon/Graphics/" .. _OPTIONS["gfx"] .. "/**.h",
                "src/Talon/Graphics/" .. _OPTIONS["gfx"] .. "/**.cpp"
            }


	-- 
	-- Client Applications
	--
	project "Sandbox"
        uuid        "16D42CD3-C21B-CD4B-9CB1-614FFAD9349F"
		targetname  "TalonSandbox"
		language    "C++"
		kind        "WindowedApp"
		flags       { "FatalWarnings", "WinMain" }
		links		{ "Talon" }

        includedirs {
            "src/Sandbox"
        }

		files {
			"src/Sandbox/*.cpp"
		}

        configuration "MacOSX"
            files {
                "src/Sandbox/Mac/**"
            }

	--
	-- dependencies
	--
	project "nowide"
        uuid "3418296C-3A22-C447-AFEC-5F6825425D99"
		language "C++"
		kind "StaticLib"

		includedirs { "externals/nowide" }
		files {
			"externals/nowide/**.cpp"
		}

	project "glew"
        uuid "C85014E5-5402-3347-AD1B-6D333E1047C3"
		language "C++"
		kind "StaticLib"
		defines "GLEW_STATIC"

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