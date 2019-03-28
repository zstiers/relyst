group_push("intermediate")
	project_module("intermediate")
		project_dependency("memory", "public")

	project_module_test("intermediate")
group_pop()