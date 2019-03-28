/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include "list.h"

#include <memory/allocator.h>
#include <string_view>

namespace relyst::intermediate::ast {

/*
 * This is a destructor-less identifier that allocates memory it does not free. This is intentional.
 * The used allocator should likely be a pool specifically for identifiers that outlives
 * the uses of them. This is because we know that the strings will be allocated in bulk
 * early in the complication process and needed through the whole process.
 */

struct Identifier : std::string_view {
    Identifier () { }
    Identifier (memory::Allocator & alloc, const std::string_view & view)
        : std::string_view(alloc.AllocN<char>(view.length()), view.length())
    {
        std::copy(view.begin(), view.end(), const_cast<char *>(data()));
    }
};

using IdentifierScoped = List<Identifier>;

} // namespace relyst::intermediate::ast