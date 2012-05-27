
function isgeneratoraction(action)
    return action ~= "clean" and action ~= nil
end

function stringfromfile(file)
    local f = io.open(file, "r")
    local t = f:read("*all")
    f:close()
    return t
end

function makedirs(t)
	for k,v in ipairs(t) do
		if not os.isdir(v) then
			os.mkdir(v)
		end
	end
end

function copy_cmd(src, dest)
	dest = dest or "bin/$(PlatformShortName)/$(Configuration)/"
	local srcAbsolute = path.translate(path.getabsolute(src))
	local destAbsolute = path.translate(path.getabsolute(dest))
	local cmd = ""
	if os.is("windows") then
		cmd = "xcopy " .. srcAbsolute .. " " .. destAbsolute .. " /Y"

		if os.isdir(src) then
			cmd = cmd .. " /E" 
		end
	else
		cmd = "cp -R " .. srcAbsolute .. " " .. destAbsolute
	end

	return cmd .. "\n"
end

function apply_external(api, lib, specifics)
	specifics=specifics or false
	local vs_specifics = ""

	if specifics then
		vs_specifics = "$(PlatformToolset)/"
	end

	configuration "vs*"
		libdirs("externals/" .. api .. "/lib/vc/" .. vs_specifics .. "$(PlatformShortName)/")
		links(lib)
	
	configuration "*"
		includedirs("externals/" .. api .. "/include/")
end