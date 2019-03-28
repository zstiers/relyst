/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include "generated/relystBaseVisitor.h"

#include <intermediate/ast.h>

namespace relyst::script {

namespace ast { using namespace ::relyst::intermediate::ast; }

class AstBuilderVisitor : private relystBaseVisitor {
    memory::Allocator & m_treeAlloc;
    memory::Allocator & m_stringAlloc;

public:
    AstBuilderVisitor (memory::Allocator & treeAlloc, memory::Allocator & stringAlloc) : m_treeAlloc(treeAlloc), m_stringAlloc(stringAlloc) { }

public:
    template <typename T>
    T Visit (antlr4::ParserRuleContext * ctx);
    template <typename T>
    bool Visit (antlr4::ParserRuleContext * ctx, T & out);
    bool Visit (antlr4::Token * token, ast::Identifier & out);

private:
    template <typename T, typename U>
    ast::List<T> CreateList (antlr4::ParserRuleContext * ctx, const std::vector<U *> & list);
    template <typename T>
    T * CreateNode (antlr4::ParserRuleContext * ctx, ast::NodeType type);

private:
    antlrcpp::Any visitCompileUnit (relystParser::CompileUnitContext * ctx) override;
    antlrcpp::Any visitDefinitionList (relystParser::DefinitionListContext * ctx) override;
    antlrcpp::Any visitNameScoped (relystParser::NameScopedContext * ctx) override;
    antlrcpp::Any visitNamespaceDefinition (relystParser::NamespaceDefinitionContext * ctx) override;
    antlrcpp::Any visitStructDefinition (relystParser::StructDefinitionContext * ctx) override;
    antlrcpp::Any visitTypeList (relystParser::TypeListContext * ctx) override;
};

} // relyst::script