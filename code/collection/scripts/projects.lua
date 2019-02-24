group_push("collection")
	project_module("code/collection")
		project_dependency("core",   "public")
		project_dependency("memory", "public")

	project_module_test("code/collection")
group_pop()