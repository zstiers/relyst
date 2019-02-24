dofile "genie/common.lua"

solution "all"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	language "C++"
	location ("../.build/projects/all/" .. _ACTION)
	flags { "CppLatest" }
	
	includedirs { "../ext/inc" }
	defines { "FMT_HEADER_ONLY" }

    configuration "Debug"
        targetdir (path.join("../.build/bin/all/" .. _ACTION, "debug"))
        flags { "Symbols" }
    configuration "Release"
        targetdir (path.join("../.build/bin/all/" .. _ACTION, "release"))

	-- Pick correct lib dirs
	configuration { "Debug", "x64" }
		libdirs { "../ext/lib/debug/" .. _ACTION .. "/x64" }
	configuration { "Release", "x64" }
		libdirs { "../ext/lib/release/" .. _ACTION .. "/x64" }

	configuration {}
	dofile "../code/modules.lua"	

	-- Prepare for include dependencies by getting all the include dirs
	local dirsInc = {}
	for i, prj in ipairs(solution().projects) do
		dirsInc[prj.name] = path.join(prj.basedir, "../inc")
	end

	-- Apply dependencies
	for i, prj in ipairs(solution().projects) do
		project(prj.name)
		project_dependencies_apply()
	end

	--startproject "example-00-helloworld"