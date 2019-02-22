
-- dir is the path to this project folder relative to the root
function project_module (dir, name)
	if name == nil then
		name = path.getbasename(dir)
	end

	project(name)
	dir = path.join("..", dir)

	kind "StaticLib"
	files {
		"../inc/**.h",
		"../inc/**.inl",
		"../src/**.h",
		"../src/**.inl",
		"../src/**.cpp",
	}
	vpaths {
		["inc/*"] = path.join(dir, "inc", "**.*"),
		["src/*"] = path.join(dir, "src", "**.*"),
	}
	includedirs { "../inc" }
end

-- dir is the path to this project folder relative to the root
function project_module_test (dir, name)
	if name == nil then
		name = path.getbasename(dir) .. "_test"
	end
	
	project(name)
	dir = path.join("../", dir)

	kind "ConsoleApp"
	files { "../test/**.cpp" }
	vpaths { ["*"] = path.join(dir, "test") }
	includedirs { "../inc" }
end

local currentGroup = {}

function group_push (grp)
	currentGroup[#currentGroup + 1] = grp
	local current = ""
	for index = 1, #currentGroup do
		current = path.join(current, currentGroup[index])
	end
	group(current)
end

function group_pop ()
	currentGroup[#currentGroup] = nil
end