group_push("core")
	project_module("code/core")

	project_module_test("code/core")
		depsLib["core_test"] = { "core" }
group_pop()