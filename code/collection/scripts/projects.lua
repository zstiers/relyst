group_push("collection")
	project_module("code/collection")
		depsInc["collection"] = { "core", "memory" }
		depsLib["collection"] = { "memory" }

	project_module_test("code/collection")
		depsInc["collection_test"] = { "core", "memory" }
		depsLib["collection_test"] = { "memory" }
group_pop()