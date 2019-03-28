/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include "../node.h"

namespace relyst::intermediate::ast {

// TODO : Support return types and const correctness. I think I need a bunch of weird template
// magic to do that, so I'll leave that for when I need it. 
template <typename Visitor>
void Visit (Visitor && vis, const Node & node) {
    const auto nodeType = node.nodeType;
    if (NodeType::kScopeFirst <= nodeType && nodeType <= NodeType::kScopeLast)
        return vis(static_cast<const Scope &>(node));
    if (NodeType::kTypeFirst <= nodeType && nodeType <= NodeType::kTypeLast)
        return vis(static_cast<const Type &>(node));
}

} // namespace relyst::intermediate::ast