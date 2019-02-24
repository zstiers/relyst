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

	-- Apply dependencies
	for i, prj in ipairs(solution().projects) do
		project(prj.name)
		project_dependencies_apply()
	end

	--startproject "example-00-helloworld"