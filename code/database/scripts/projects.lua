group_push("database")
	project_module("database")
		project_dependency("collection", "public")
		project_dependency("core", "public")
		project_dependency("memory", "public")

	project_module_test("database")
group_pop()