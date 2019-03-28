
// Generated from ../relyst.g4 by ANTLR 4.7.1

#pragma once


#include <antlr4/antlr4-runtime.h>
#include "relystVisitor.h"


/**
 * This class provides an empty implementation of relystVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  relystBaseVisitor : public relystVisitor {
public:

  virtual antlrcpp::Any visitCompileUnit(relystParser::CompileUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefinition(relystParser::DefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefinitionList(relystParser::DefinitionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNameScoped(relystParser::NameScopedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNamespaceDefinition(relystParser::NamespaceDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStructDefinition(relystParser::StructDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitType(relystParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeList(relystParser::TypeListContext *ctx) override {
    return visitChildren(ctx);
  }


};

