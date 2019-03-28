dofile "genie/common.lua"

solution "all"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	language "C++"
	location ("../.build/projects/all/" .. _ACTION)
	flags { "CppLatest" }
	
	includedirs { "../ext/inc" }

    configuration "Debug"
        targetdir (path.join("../.build/bin/all/" .. _ACTION, "debug"))
        flags { "Symbols" }
		defines { "RELYST_DEBUG=1" }
    configuration "Release"
        targetdir (path.join("../.build/bin/all/" .. _ACTION, "release"))
		defines { "RELYST_DEBUG=0" }

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