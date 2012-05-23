
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