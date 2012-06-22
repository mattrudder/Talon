--
-- Jansson (dependency)
--
project "jansson"
    uuid "53B9A936-AF58-11E1-8974-BA116188709B"
	language "C++"
	kind "StaticLib"
	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs { "src" }
	files {
		"src/*.c",
		"src/*.h",
	}