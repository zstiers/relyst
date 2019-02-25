group_push("relyst")
	for i, dir in ipairs(os.matchdirs("*")) do
		dofile(path.join(dir, "scripts/projects.lua"))
	end
group_pop()