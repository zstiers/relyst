/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include "const.h"
#include "identifier.h"
#include "list.h"

namespace relyst::intermediate::ast {

/*
 * Node classes are all destructor-less types. Every tree has an allocator associated with it in which all the allocations
 * are done, but orphaned. The used allocator must be designed for this to be the case to avoid a leak. Nodes
 * are *NOT* expected to free the memory they allocate as they should instead be using an allocator that deallocates
 * the entire tree at once (probably a chunked linear allocator).
 */

struct Node {
    NodeKind kind = NodeKind::kInvalid;

#if RELYST_AST_FORCE_NODE_POLYMORPHISM
    virtual ~Node () { }
#endif
};

/*
 * Individual node types. Uses an enum to safely downcast.
 */

struct Scope : Node {
    Identifier   name;
    List<Node *> children;
};

struct Type : Node {
    Identifier             name;
    List<IdentifierScoped> bases;
};

} // namespace relyst::intermediate::ast

#include "detail/node.inl"