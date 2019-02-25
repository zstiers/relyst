group_push("collection")
	project_module("collection")
		project_dependency("core",   "public")
		project_dependency("memory", "public")

	project_module_test("collection")
group_pop()