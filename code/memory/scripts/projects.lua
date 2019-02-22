group_push("memory")
	project_module("code/memory")

	project_module_test("code/memory")
		depsLib["memory_test"] = { "memory" }
group_pop()