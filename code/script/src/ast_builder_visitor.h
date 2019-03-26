/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#pragma once

#include "generated/relystBaseVisitor.h"

#include <intermediate/ast.h>

namespace relyst::script {

class AstBuilderVisitor : private relystBaseVisitor {
public:
    intermediate::ast::NodePtr Visit (antlr4::ParserRuleContext * ctx);

private:
    template <typename T>
    intermediate::ast::NodePtr CreateList (antlr4::ParserRuleContext * ctx, const std::vector<T *> & list);
    intermediate::ast::NodePtr CreateNode (antlr4::ParserRuleContext * ctx);

private:
    antlrcpp::Any visitCompileUnit (relystParser::CompileUnitContext * ctx) override;
    antlrcpp::Any visitDefinitionList (relystParser::DefinitionListContext * ctx) override;
    antlrcpp::Any visitName (relystParser::NameContext * ctx) override;
    antlrcpp::Any visitNameScoped (relystParser::NameScopedContext * ctx) override;
    antlrcpp::Any visitNamespaceDefinition (relystParser::NamespaceDefinitionContext * ctx) override;
    antlrcpp::Any visitStructDefinition (relystParser::StructDefinitionContext * ctx) override;
    antlrcpp::Any visitTypeList (relystParser::TypeListContext * ctx) override;
};

} // relyst::script