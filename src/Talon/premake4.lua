
local dxPath = os.getenv("DXSDK_DIR")
    
-- 
-- Talon Engine
-- 
project "Talon"
    uuid        "67ED9308-E1BE-D947-AB41-04EC07B52663"
	targetname  "Talon"
	language    "C++"
	kind        "SharedLib"
	defines     { "ZLIB_DLL", "ZLIB_WINAPI","TALON_DLL", "BUILDING_TALON"  }
	flags       { "FatalWarnings" }

	--pchheader	"TalonPrefix.h"
	--pchsource	"TalonPrefix.cpp"

	files {
		"../../include/Talon/*.h",
		"../../include/Talon/Graphics/*.h",
        "../../src/Talon/Graphics/" .. _OPTIONS["gfx"] .. "/**.cpp",
        "../../src/Talon/Graphics/" .. _OPTIONS["gfx"] .. "/**.h",
		"../../include/Talon/Input/*.h",
        "../../include/Talon/Math/*.h",
        "../../include/Talon/Math/*.inl",
		"../../include/Talon/Platform/*.h",

		"TalonPrefix.h",
		"*.cpp",
		"Graphics/*.cpp",
		"Input/*.cpp",
		"Platform/*.cpp",
	}

	includedirs {
		"../../build",
		"./",
		"../../externals/nowide",
		"../../externals/glew-1.7.0/include",
	}

	apply_external("freeimage-3.15.3", "FreeImage")
	apply_external("cairo-1.8.8", "cairo", true)
	apply_external("libpng-1.5.10", "libpng15", true)
	apply_external("zlib-1.2.6", "zlibwapi", true)

	-- Configuration
	configuration "Release"
		flags { "OptimizeSpeed" }

    -- Generic platform includes
    configuration "Windows"
        links { "nowide" }
    	defines { "_CRT_SECURE_NO_WARNINGS" }
        files {
            "../../include/Talon/Platform/Win32/**.h",
            "../../include/Talon/Math/SSE/*.h",
            "../../include/Talon/Math/SSE/*.inl",
			"Input/RawInput/**.h",
        	"Input/RawInput/**.cpp",
			"Input/XInput/**.h",
        	"Input/XInput/**.cpp",
            "Platform/Win32/**.cpp"
        }
        links { "xinput" }
        postbuildcommands
        {
            copy_cmd("../../externals/freeimage-3.15.3/lib/vc/$(PlatformShortName)/FreeImage.dll") ..
            copy_cmd("../../externals/cairo-1.8.8/lib/vc/$(PlatformToolset)/$(PlatformShortName)/cairo.dll") ..
            copy_cmd("../../externals/libpng-1.5.10/lib/vc/$(PlatformToolset)/$(PlatformShortName)/libpng15.dll") ..
            copy_cmd("../../externals/zlib-1.2.6/lib/vc/$(PlatformToolset)/$(PlatformShortName)/zlibwapi.dll")
        }

    configuration "MacOSX"
        files {
            "../../include/Talon/Platform/Mac/**.h",
            "Platform/Mac/**.cpp",
            "Platform/Mac/**.m",
            "Platform/Mac/**.mm"
        }
        buildoptions { "-x objective-c++", "-fobjc-arc", "-std=c++11", "-stdlib=libc++"}

    configuration "OpenGL"
        defines { "GLEW_STATIC", "TALON_OPENGL" }
        links { "glew" }

    configuration "Direct3D11"
    	defines 	{ "TALON_D3D11" }
    	--includedirs { path.translate(path.join(dxPath, "Include")) }
    	libdirs 	{ path.translate(path.join(dxPath, "Lib/$(PlatformShortName)")) }
    	links		{ "dxguid", "dxgi", "d3d11", "d3dcompiler" }
