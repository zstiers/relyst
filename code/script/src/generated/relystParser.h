
// Generated from ../relyst.g4 by ANTLR 4.7.1

#pragma once


#include <antlr4/antlr4-runtime.h>




class  relystParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    COMPONENT = 8, STRUCT = 9, ID = 10, BLOCK_COMMENT = 11, LINE_COMMENT = 12, 
    WHITE_SPACE = 13
  };

  enum {
    RuleCompileUnit = 0, RuleDefinition = 1, RuleDefinitionList = 2, RuleNameScoped = 3, 
    RuleNamespaceDefinition = 4, RuleStructDefinition = 5, RuleType = 6, 
    RuleTypeList = 7
  };

  relystParser(antlr4::TokenStream *input);
  ~relystParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class CompileUnitContext;
  class DefinitionContext;
  class DefinitionListContext;
  class NameScopedContext;
  class NamespaceDefinitionContext;
  class StructDefinitionContext;
  class TypeContext;
  class TypeListContext; 

  class  CompileUnitContext : public antlr4::ParserRuleContext {
  public:
    CompileUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    DefinitionListContext *definitionList();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CompileUnitContext* compileUnit();

  class  DefinitionContext : public antlr4::ParserRuleContext {
  public:
    DefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NamespaceDefinitionContext *namespaceDefinition();
    StructDefinitionContext *structDefinition();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DefinitionContext* definition();

  class  DefinitionListContext : public antlr4::ParserRuleContext {
  public:
    DefinitionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DefinitionContext *> definition();
    DefinitionContext* definition(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DefinitionListContext* definitionList();

  class  NameScopedContext : public antlr4::ParserRuleContext {
  public:
    NameScopedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NameScopedContext* nameScoped();

  class  NamespaceDefinitionContext : public antlr4::ParserRuleContext {
  public:
    NamespaceDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameScopedContext *nameScoped();
    DefinitionListContext *definitionList();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamespaceDefinitionContext* namespaceDefinition();

  class  StructDefinitionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *kind = nullptr;;
    antlr4::Token *name = nullptr;;
    StructDefinitionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TypeListContext *typeList();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COMPONENT();
    antlr4::tree::TerminalNode *STRUCT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StructDefinitionContext* structDefinition();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NameScopedContext *nameScoped();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  TypeListContext : public antlr4::ParserRuleContext {
  public:
    TypeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeListContext* typeList();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

