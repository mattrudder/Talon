--
-- Nowide (Windows dependency)
--
project "nowide"
    uuid "3418296C-3A22-C447-AFEC-5F6825425D99"
	language "C++"
	kind "StaticLib"

	includedirs { "./" }
	files {
		"**.cpp"
	}
