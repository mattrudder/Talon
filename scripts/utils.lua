
function isgeneratoraction(action)
    return action ~= "clean" and action ~= nil
end

function stringfromfile(file)
    local f = io.open(file, "r")
    local t = f:read("*all")
    f:close()
    return t
end

function trim(s)
	return s:find'^%s*$' and '' or s:match'^%s*(.*%S)'
end

function makedirs(t)
	for k,v in ipairs(t) do
		if not os.isdir(v) then
			os.mkdir(v)
		end
	end
end

function copy_cmd(src, dest)
	dest = dest or get_absolute_from_solution("bin/$(PlatformShortName)/$(Configuration)/")
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

function get_absolute_from_solution(p)
	local sol = solution()
   	return path.getabsolute(path.join(sol.basedir, p))
end

function apply_external(api, lib, specifics)
	specifics=specifics or false
	local vs_specifics = ""

	if specifics then
		vs_specifics = "$(PlatformToolset)/"
	end

	configuration "vs*"
		libdirs(get_absolute_from_solution("externals/" .. api .. "/lib/vc/" .. vs_specifics .. "$(PlatformShortName)/"))

	configuration "MacOSX"
		libdirs(get_absolute_from_solution("externals/" .. api .. "/lib/Mac/"))
	
	configuration "*"
		links(lib)
		includedirs(get_absolute_from_solution("externals/" .. api .. "/include/"))
end