/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include <memory>
#include <string>
#include <variant>
#include <vector>

#define RELYST_AST_KEEP_DEBUG_INFO 1

namespace relyst::intermediate::ast {

struct SourceLocation {
    std::size_t line           = 0;
    std::size_t positionOnLine = 0;
};

struct DebugInfo {
    SourceLocation sourceStart;
    SourceLocation sourceStop;
};

struct Node;

using NodePtr = std::shared_ptr<Node>;

enum class BinaryOperation {
};

enum class UnaryOperation {
};

using Identifier = std::string;
using List       = std::vector<NodePtr>;

struct BinaryExpression {
    NodePtr operation;
    NodePtr left;
    NodePtr right;
};

struct UnaryExpression {
    NodePtr operation;
    NodePtr operand;
};

struct Scope {
    NodePtr data;
};

struct ScopeNamed : Scope {
    NodePtr name;
};

struct Struct {
    NodePtr name;
    NodePtr bases;
};

struct Node {
    std::variant<std::monostate, BinaryExpression, BinaryOperation, Identifier, List, Scope, ScopeNamed, Struct, UnaryExpression, UnaryOperation> v;

private:
#if RELYST_AST_KEEP_DEBUG_INFO
    DebugInfo debugInfo;
public:
    DebugInfo *       GetDebugInfo ()       { return &debugInfo; }
    const DebugInfo * GetDebugInfo () const { return &debugInfo; }
#else
public:
    DebugInfo *       GetDebugInfo ()       { return nullptr; }
    const DebugInfo * GetDebugInfo () const { return nullptr; }
#endif
};

} // namespace relyst::intermediate::ast