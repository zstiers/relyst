group_push("runtime")
	project_module("runtime")
		project_dependency("collection", "public")
		project_dependency("core", "public")
		project_dependency("memory", "public")

	project_module_test("runtime")
group_pop()