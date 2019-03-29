/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include "ast.h"
#include "symbol/const.h"

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace relyst::intermediate::symbol {

template <typename T>
using SymbolPtr = std::shared_ptr<T>;

struct Base {
    virtual ~Base () {}
};

struct Type : Base {
    struct Member {
        SymbolPtr<Type> type;
    };

    TypeKind    typeKind = TypeKind::kInvalid;
    std::size_t bytes    = 0;
    std::size_t customId = 0;

    std::vector<SymbolPtr<Type>>            bases;
    std::unordered_map<std::string, Member> members;
};

struct Scope : Base {
    std::unordered_map<std::string, SymbolPtr<Base>> children;
};

// The shared table contains all symbols shared by everything. This is because I don't
// require ordering so this should be prebuilt. For symbols that do require order, such
// as function bodies, a different stack-based approach will be used instead.
class TableShared {
public:
    Scope m_globalScope;

public:
    TableShared (const ast::Node * astRoot);
};

} // namespace relyst::intermediate::symbol