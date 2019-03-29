/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#include "ast_builder_visitor.h"

#include <variant>

namespace relyst::script {

template <typename T, typename U>
ast::List<T> AstBuilderVisitor::CreateList (antlr4::ParserRuleContext * ctx, const std::vector<U *> & list) {
    ast::List<T> ret(m_treeAlloc, list.size());
    T childOut;
    for (auto * childIn : list) {
        if (Visit(childIn, childOut))
            ret.Push(childOut);
    }
    return ret;
}

template <typename T>
T * AstBuilderVisitor::CreateNode (antlr4::ParserRuleContext * ctx, ast::NodeKind kind) {
    auto ret  = m_treeAlloc.Alloc<T>();
    ret->kind = kind;
    return ret;
}

template <typename T>
T AstBuilderVisitor::Visit (antlr4::ParserRuleContext * ctx) {
    T ret;
    Visit(ctx, ret);
    return ret;
}

template <typename T>
bool AstBuilderVisitor::Visit (antlr4::ParserRuleContext * ctx, T & out) {
    if (ctx) {
        auto ret = visit(ctx);
        if (ret.isNotNull()) {
            out = ret.as<T>();
            return true;
        }
    }
    out = T();
    return false;
}

bool AstBuilderVisitor::Visit (antlr4::Token * token, ast::Identifier & out) {
    out = ast::Identifier(m_stringAlloc, token->getText());
    return true;
}

antlrcpp::Any AstBuilderVisitor::visitCompileUnit (relystParser::CompileUnitContext * ctx) {
    auto ret = CreateNode<ast::Scope>(ctx, ast::NodeKind::kRoot);
    Visit(ctx->definitionList(), ret->children);
    return static_cast<ast::Node *>(ret);
}

antlrcpp::Any AstBuilderVisitor::visitDefinitionList (relystParser::DefinitionListContext * ctx) {
    return CreateList<ast::Node *>(ctx, ctx->definition());
}

antlrcpp::Any AstBuilderVisitor::visitNameScoped (relystParser::NameScopedContext * ctx) {
    const auto ids = ctx->ID();
    ast::IdentifierScoped ret(m_treeAlloc, ids.size());
    for (const auto & id : ids)
        ret.Push(ast::Identifier(m_stringAlloc, id->getText()));
    return ret;
}

antlrcpp::Any AstBuilderVisitor::visitNamespaceDefinition (relystParser::NamespaceDefinitionContext * ctx) {
    // Namespace syntax supports nesting, but my AST doesn't. These will get expanded to multiple nodes.
    // The way it works is we return the node for the first namespace which already has the others nested in it.
    // All the visits though happen in the furthest nested namespace.
    auto ids  = Visit<ast::IdentifierScoped>(ctx->nameScoped());
    auto iter = ids.begin();
    auto end  = ids.end();

    // Do the first node manually.
    auto outer  = CreateNode<ast::Scope>(ctx, ast::NodeKind::kNamespace);
    outer->name = *iter;

    // Chain in the rest of the nodes. After this `inner` should be the inner-most node.
    auto inner = outer;
    for (++iter; iter != end; ++iter) {
        auto next  = CreateNode<ast::Scope>(ctx, ast::NodeKind::kNamespace);
        next->name = *iter;
        inner->children = ast::List<ast::Node *>(m_treeAlloc, 1);
        inner->children.Push(next);
        inner = next;
    }

    // Now we can complete construction of the `inner` by filling the children.
    Visit(ctx->definitionList(), inner->children);
    return static_cast<ast::Node *>(outer);
}

antlrcpp::Any AstBuilderVisitor::visitStructDefinition (relystParser::StructDefinitionContext * ctx) {
    ast::NodeKind kind = ast::NodeKind::kInvalid;
    switch (ctx->kind->getType()) {
        case relystParser::COMPONENT: kind = ast::NodeKind::kComponent; break;
        case relystParser::STRUCT:    kind = ast::NodeKind::kStruct;    break;
    }

    auto ret = CreateNode<ast::Type>(ctx, kind);
    Visit(ctx->name,       ret->name);
    Visit(ctx->typeList(), ret->bases);
    return static_cast<ast::Node *>(ret);
}

antlrcpp::Any AstBuilderVisitor::visitTypeList (relystParser::TypeListContext * ctx) {
    return CreateList<ast::IdentifierScoped>(ctx, ctx->type());
}

} // relyst::script