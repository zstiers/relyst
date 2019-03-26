group_push("script")
	project_module("script")
		defines { "ANTLR4CPP_STATIC", "_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING" }
		project_dependency("antlr4-runtime-static", "private")
		project_dependency("intermediate", "public")

	project_module_test("script")
group_pop()