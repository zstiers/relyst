
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

local projectDeps      = { }
local projectHasSource = { }

function project_dependency(dependsOn, scope)
	local prj = project()
	if projectDeps[prj.name] == nil then
		projectDeps[prj.name] = { }
	end
	projectDeps[prj.name][dependsOn] = { scope = scope }
end

function project_dependencies_apply_internal(recursePrjName, allowPrivateIncludes, traversed)
	if traversed[recursePrjName] then
		return
	end
	traversed[recursePrjName] = true
	local prjDeps = projectDeps[recursePrjName]
	if prjDeps then
		for key, dep in pairs(prjDeps) do
			if allowPrivateIncludes or dep.scope == "public" then
				local prevPrjName = project().name
				local includeDir  = path.join(project(key).basedir, "../inc")
				project(prevPrjName)
				includedirs(includeDir)
			end
			if projectHasSource[key] then
				links(key)
			end
			project_dependencies_apply_internal(key, false, traversed)
		end
	end
end

function project_dependencies_apply()
	local prjName = project().name
	project_dependencies_apply_internal(prjName, true, {})
	removelinks(prjName)
end

-- dir is the path to this project folder relative to the root
function project_module (name)
	local dir = path.getrelative(solution().basedir, path.join(os.getcwd(), ".."))
	project(name)

	kind "StaticLib"
	files {
		"../inc/**.h",
		"../inc/**.inl",
		"../src/**.h",
		"../src/**.inl",
		"../src/**.cpp",
		"../scripts/**.*",
	}
	vpaths {
		["inc/*"]     = path.join(dir, "inc", "**.*"),
		["src/*"]     = path.join(dir, "src", "**.*"),
		["scripts/*"] = path.join(dir, "scripts", "**.*"),
	}

	project_dependency(name, "private")
	projectHasSource[name] = next(os.matchfiles("../src/**.cpp")) ~= nil
end

-- dir is the path to this project folder relative to the root
function project_module_test (name)
	local dir = path.getrelative(solution().basedir, path.join(os.getcwd(), ".."))
	project(name .. "_test")

	kind "ConsoleApp"
	files { "../test/**.cpp" }
	vpaths { ["*"] = path.join(dir, "test") }

	project_dependency(name, "private")
end