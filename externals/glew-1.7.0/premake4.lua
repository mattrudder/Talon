--
-- Glew (dependency)
--
project "glew"
    uuid "C85014E5-5402-3347-AD1B-6D333E1047C3"
	language "C++"
	kind "StaticLib"
	defines "GLEW_STATIC"

	includedirs { "include" }
	files {
		"src/glew.c"
	}