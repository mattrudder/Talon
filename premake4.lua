---
--- Premake build script for Talon Game Tech
---

dofile("scripts/utils.lua")

local localHostName = trim(os.getenv("COMPUTERNAME") or os.outputof("hostname -s"))
local codeGenPath = path.getabsolute("bin/Debug/Talon.CodeGenerator.exe")

if not _OPTIONS["to"] then
	if _ACTION then
		_OPTIONS["to"] = "build/generated/" .. _ACTION
	else
		_OPTIONS["to"] = "build/generated/"
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

--if not _OPTIONS["scripts"] then
--	_OPTIONS["scripts"] = "Scripts"
--end

-- Code generator not yet ready for use.
-- if not os.isfile(codeGenPath) then
--     print "WARN: Code generator has not been built. Please build the project in tools/Talon.CodeGenerator."
-- else
--     print "Processing definitions..."
--     if os.is("windows") then
--         os.execute(codeGenPath)
--     else
--         os.execute("mono " .. codeGenPath)
--     end
-- end

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

	configuration "MacOSX"
		buildoptions { "-x objective-c++", "-std=c++11", "-stdlib=libc++" }


include "src"
include "experimental"
include "externals"
include "tests"

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

newoption {
	trigger = "with-awesomium",
	description = "Enables the use of Awesomium for rendering HTML-based UI."
}