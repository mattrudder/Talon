--
-- UnitTest++ (dependency)
--
project "UnitTest++"
    uuid "73749C7B-7271-4C48-8C7E-1DF0D5DB04BD"
	language "C++"
	kind "StaticLib"
	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs { "src" }
	files {
		"src/*.h",
		"src/*.cpp"
	}

	configuration "windows"
		files {
			"src/Win32/*.h",
			"src/Win32/*.cpp"
		}

	configuration "macosx or linux"
		files {
			"src/Posix/*.h",
			"src/Posix/*.cpp"
		}