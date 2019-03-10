/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

 // Crap for leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>

void MemoryLeakDetection () {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

#include <database/database.h>
#include <memory/allocator_linear.h>

struct Position {
    static constexpr relyst::database::ComponentKey ComponentKey = 1;
    float x, y, z;
};

struct Velocity {
    static constexpr relyst::database::ComponentKey ComponentKey = 2;
    float x, y, z;
};

int main()
{
    MemoryLeakDetection();

    relyst::database::Database db;
    auto row = db.CreateRow();
    db.AddComponent(row, Position{ 5.0f, 2.5f, 3.0f });
    db.AddComponent(row, Velocity{ 0.0f, 1.0f, -1.0f });
    db.RemoveComponent<Position>(row);

	return 0;
}