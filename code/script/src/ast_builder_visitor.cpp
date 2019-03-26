/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#include "ast_builder_visitor.h"

#include <iostream>

namespace relyst::script {

template <typename T>
intermediate::ast::NodePtr AstBuilderVisitor::CreateList (antlr4::ParserRuleContext * ctx, const std::vector<T *> & list) {
    auto   ret = CreateNode(ctx);
    auto & v   = ret->v.emplace<relyst::intermediate::ast::List>();
    v.reserve(list.size());
    for (auto * child : list) {
        auto node = Visit(child);
        if (node)
            v.push_back(node);
    }
    return ret;
}

intermediate::ast::NodePtr AstBuilderVisitor::CreateNode (antlr4::ParserRuleContext * ctx) {
    auto ret = std::make_shared<relyst::intermediate::ast::Node>();
    if (auto * debugInfo = ret->GetDebugInfo()) {
        debugInfo->sourceStart.line           = ctx->getStart()->getLine();
        debugInfo->sourceStart.positionOnLine = ctx->getStart()->getCharPositionInLine();
        debugInfo->sourceStop.line            = ctx->getStop()->getLine();
        debugInfo->sourceStop.positionOnLine  = ctx->getStop()->getCharPositionInLine();
    }
    return ret;
}

intermediate::ast::NodePtr AstBuilderVisitor::Visit (antlr4::ParserRuleContext * ctx) {
    if (ctx) {
        auto ret = visit(ctx);
        if (ret.isNotNull())
            return std::move(ret.as<intermediate::ast::NodePtr>());
    }
    return intermediate::ast::NodePtr();
}

antlrcpp::Any AstBuilderVisitor::visitCompileUnit (relystParser::CompileUnitContext * ctx) {
    auto   ret = CreateNode(ctx);
    auto & v   = ret->v.emplace<intermediate::ast::Scope>();
    v.data = Visit(ctx->definitionList());
    return ret;
}

antlrcpp::Any AstBuilderVisitor::visitDefinitionList (relystParser::DefinitionListContext * ctx) {
    return CreateList(ctx, ctx->definition());
}

antlrcpp::Any AstBuilderVisitor::visitName (relystParser::NameContext * ctx) {
    auto ret = CreateNode(ctx);
    ret->v.emplace<intermediate::ast::Identifier>(ctx->getText());
    return ret;
}

antlrcpp::Any AstBuilderVisitor::visitNameScoped (relystParser::NameScopedContext * ctx) {
    return CreateList(ctx, ctx->name());
}

antlrcpp::Any AstBuilderVisitor::visitNamespaceDefinition (relystParser::NamespaceDefinitionContext * ctx) {
    auto   ret = CreateNode(ctx);
    auto & v   = ret->v.emplace<intermediate::ast::ScopeNamed>();
    v.data = Visit(ctx->definitionList());
    v.name = Visit(ctx->nameScoped());
    return ret;
}

antlrcpp::Any AstBuilderVisitor::visitStructDefinition (relystParser::StructDefinitionContext * ctx) {
    auto   ret = CreateNode(ctx);
    auto & v   = ret->v.emplace<intermediate::ast::Struct>();
    v.name  = Visit(ctx->name());
    v.bases = Visit(ctx->typeList());
    return ret;
}

antlrcpp::Any AstBuilderVisitor::visitTypeList (relystParser::TypeListContext * ctx) {
    return CreateList(ctx, ctx->type());
}

} // relyst::script