
// Generated from ../relyst.g4 by ANTLR 4.7.1

#pragma once


#include <antlr4/antlr4-runtime.h>
#include "relystParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by relystParser.
 */
class  relystVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by relystParser.
   */
    virtual antlrcpp::Any visitCompileUnit(relystParser::CompileUnitContext *context) = 0;

    virtual antlrcpp::Any visitDefinition(relystParser::DefinitionContext *context) = 0;

    virtual antlrcpp::Any visitDefinitionList(relystParser::DefinitionListContext *context) = 0;

    virtual antlrcpp::Any visitName(relystParser::NameContext *context) = 0;

    virtual antlrcpp::Any visitNameScoped(relystParser::NameScopedContext *context) = 0;

    virtual antlrcpp::Any visitNamespaceDefinition(relystParser::NamespaceDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitStructDefinition(relystParser::StructDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitType(relystParser::TypeContext *context) = 0;

    virtual antlrcpp::Any visitTypeList(relystParser::TypeListContext *context) = 0;


};

