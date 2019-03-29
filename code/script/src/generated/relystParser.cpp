
// Generated from ../relyst.g4 by ANTLR 4.7.1


#include "relystVisitor.h"

#include "relystParser.h"


using namespace antlrcpp;
using namespace antlr4;

relystParser::relystParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

relystParser::~relystParser() {
  delete _interpreter;
}

std::string relystParser::getGrammarFileName() const {
  return "relyst.g4";
}

const std::vector<std::string>& relystParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& relystParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- CompileUnitContext ------------------------------------------------------------------

relystParser::CompileUnitContext::CompileUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* relystParser::CompileUnitContext::EOF() {
  return getToken(relystParser::EOF, 0);
}

relystParser::DefinitionListContext* relystParser::CompileUnitContext::definitionList() {
  return getRuleContext<relystParser::DefinitionListContext>(0);
}


size_t relystParser::CompileUnitContext::getRuleIndex() const {
  return relystParser::RuleCompileUnit;
}

antlrcpp::Any relystParser::CompileUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<relystVisitor*>(visitor))
    return parserVisitor->visitCompileUnit(this);
  else
    return visitor->visitChildren(this);
}

relystParser::CompileUnitContext* relystParser::compileUnit() {
  CompileUnitContext *_localctx = _tracker.createInstance<CompileUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, relystParser::RuleCompileUnit);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(17);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << relystParser::T__2)
      | (1ULL << relystParser::COMPONENT)
      | (1ULL << relystParser::STRUCT))) != 0)) {
      setState(16);
      definitionList();
    }
    setState(19);
    match(relystParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefinitionContext ------------------------------------------------------------------

relystParser::DefinitionContext::DefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

relystParser::NamespaceDefinitionContext* relystParser::DefinitionContext::namespaceDefinition() {
  return getRuleContext<relystParser::NamespaceDefinitionContext>(0);
}

relystParser::StructDefinitionContext* relystParser::DefinitionContext::structDefinition() {
  return getRuleContext<relystParser::StructDefinitionContext>(0);
}


size_t relystParser::DefinitionContext::getRuleIndex() const {
  return relystParser::RuleDefinition;
}

antlrcpp::Any relystParser::DefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<relystVisitor*>(visitor))
    return parserVisitor->visitDefinition(this);
  else
    return visitor->visitChildren(this);
}

relystParser::DefinitionContext* relystParser::definition() {
  DefinitionContext *_localctx = _tracker.createInstance<DefinitionContext>(_ctx, getState());
  enterRule(_localctx, 2, relystParser::RuleDefinition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(23);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case relystParser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(21);
        namespaceDefinition();
        break;
      }

      case relystParser::COMPONENT:
      case relystParser::STRUCT: {
        enterOuterAlt(_localctx, 2);
        setState(22);
        structDefinition();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefinitionListContext ------------------------------------------------------------------

relystParser::DefinitionListContext::DefinitionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<relystParser::DefinitionContext *> relystParser::DefinitionListContext::definition() {
  return getRuleContexts<relystParser::DefinitionContext>();
}

relystParser::DefinitionContext* relystParser::DefinitionListContext::definition(size_t i) {
  return getRuleContext<relystParser::DefinitionContext>(i);
}


size_t relystParser::DefinitionListContext::getRuleIndex() const {
  return relystParser::RuleDefinitionList;
}

antlrcpp::Any relystParser::DefinitionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<relystVisitor*>(visitor))
    return parserVisitor->visitDefinitionList(this);
  else
    return visitor->visitChildren(this);
}

relystParser::DefinitionListContext* relystParser::definitionList() {
  DefinitionListContext *_localctx = _tracker.createInstance<DefinitionListContext>(_ctx, getState());
  enterRule(_localctx, 4, relystParser::RuleDefinitionList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(25);
      definition();
      setState(29);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == relystParser::T__0) {
        setState(26);
        match(relystParser::T__0);
        setState(31);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(34); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << relystParser::T__2)
      | (1ULL << relystParser::COMPONENT)
      | (1ULL << relystParser::STRUCT))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NameScopedContext ------------------------------------------------------------------

relystParser::NameScopedContext::NameScopedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> relystParser::NameScopedContext::ID() {
  return getTokens(relystParser::ID);
}

tree::TerminalNode* relystParser::NameScopedContext::ID(size_t i) {
  return getToken(relystParser::ID, i);
}


size_t relystParser::NameScopedContext::getRuleIndex() const {
  return relystParser::RuleNameScoped;
}

antlrcpp::Any relystParser::NameScopedContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<relystVisitor*>(visitor))
    return parserVisitor->visitNameScoped(this);
  else
    return visitor->visitChildren(this);
}

relystParser::NameScopedContext* relystParser::nameScoped() {
  NameScopedContext *_localctx = _tracker.createInstance<NameScopedContext>(_ctx, getState());
  enterRule(_localctx, 6, relystParser::RuleNameScoped);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(40);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(36);
        match(relystParser::ID);
        setState(37);
        match(relystParser::T__1); 
      }
      setState(42);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
    setState(43);
    match(relystParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamespaceDefinitionContext ------------------------------------------------------------------

relystParser::NamespaceDefinitionContext::NamespaceDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

relystParser::NameScopedContext* relystParser::NamespaceDefinitionContext::nameScoped() {
  return getRuleContext<relystParser::NameScopedContext>(0);
}

relystParser::DefinitionListContext* relystParser::NamespaceDefinitionContext::definitionList() {
  return getRuleContext<relystParser::DefinitionListContext>(0);
}


size_t relystParser::NamespaceDefinitionContext::getRuleIndex() const {
  return relystParser::RuleNamespaceDefinition;
}

antlrcpp::Any relystParser::NamespaceDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<relystVisitor*>(visitor))
    return parserVisitor->visitNamespaceDefinition(this);
  else
    return visitor->visitChildren(this);
}

relystParser::NamespaceDefinitionContext* relystParser::namespaceDefinition() {
  NamespaceDefinitionContext *_localctx = _tracker.createInstance<NamespaceDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 8, relystParser::RuleNamespaceDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(45);
    match(relystParser::T__2);
    setState(46);
    nameScoped();
    setState(47);
    match(relystParser::T__3);
    setState(49);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << relystParser::T__2)
      | (1ULL << relystParser::COMPONENT)
      | (1ULL << relystParser::STRUCT))) != 0)) {
      setState(48);
      definitionList();
    }
    setState(51);
    match(relystParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StructDefinitionContext ------------------------------------------------------------------

relystParser::StructDefinitionContext::StructDefinitionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

relystParser::TypeListContext* relystParser::StructDefinitionContext::typeList() {
  return getRuleContext<relystParser::TypeListContext>(0);
}

tree::TerminalNode* relystParser::StructDefinitionContext::ID() {
  return getToken(relystParser::ID, 0);
}

tree::TerminalNode* relystParser::StructDefinitionContext::COMPONENT() {
  return getToken(relystParser::COMPONENT, 0);
}

tree::TerminalNode* relystParser::StructDefinitionContext::STRUCT() {
  return getToken(relystParser::STRUCT, 0);
}


size_t relystParser::StructDefinitionContext::getRuleIndex() const {
  return relystParser::RuleStructDefinition;
}

antlrcpp::Any relystParser::StructDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<relystVisitor*>(visitor))
    return parserVisitor->visitStructDefinition(this);
  else
    return visitor->visitChildren(this);
}

relystParser::StructDefinitionContext* relystParser::structDefinition() {
  StructDefinitionContext *_localctx = _tracker.createInstance<StructDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 10, relystParser::RuleStructDefinition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(53);
    dynamic_cast<StructDefinitionContext *>(_localctx)->kind = _input->LT(1);
    _la = _input->LA(1);
    if (!(_la == relystParser::COMPONENT

    || _la == relystParser::STRUCT)) {
      dynamic_cast<StructDefinitionContext *>(_localctx)->kind = _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(54);
    dynamic_cast<StructDefinitionContext *>(_localctx)->name = match(relystParser::ID);
    setState(55);
    match(relystParser::T__5);
    setState(56);
    typeList();
    setState(57);
    match(relystParser::T__0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext ------------------------------------------------------------------

relystParser::TypeContext::TypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

relystParser::NameScopedContext* relystParser::TypeContext::nameScoped() {
  return getRuleContext<relystParser::NameScopedContext>(0);
}


size_t relystParser::TypeContext::getRuleIndex() const {
  return relystParser::RuleType;
}

antlrcpp::Any relystParser::TypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<relystVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

relystParser::TypeContext* relystParser::type() {
  TypeContext *_localctx = _tracker.createInstance<TypeContext>(_ctx, getState());
  enterRule(_localctx, 12, relystParser::RuleType);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    nameScoped();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeListContext ------------------------------------------------------------------

relystParser::TypeListContext::TypeListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<relystParser::TypeContext *> relystParser::TypeListContext::type() {
  return getRuleContexts<relystParser::TypeContext>();
}

relystParser::TypeContext* relystParser::TypeListContext::type(size_t i) {
  return getRuleContext<relystParser::TypeContext>(i);
}


size_t relystParser::TypeListContext::getRuleIndex() const {
  return relystParser::RuleTypeList;
}

antlrcpp::Any relystParser::TypeListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<relystVisitor*>(visitor))
    return parserVisitor->visitTypeList(this);
  else
    return visitor->visitChildren(this);
}

relystParser::TypeListContext* relystParser::typeList() {
  TypeListContext *_localctx = _tracker.createInstance<TypeListContext>(_ctx, getState());
  enterRule(_localctx, 14, relystParser::RuleTypeList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(66);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(61);
        type();
        setState(62);
        match(relystParser::T__6); 
      }
      setState(68);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
    setState(69);
    type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> relystParser::_decisionToDFA;
atn::PredictionContextCache relystParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN relystParser::_atn;
std::vector<uint16_t> relystParser::_serializedATN;

std::vector<std::string> relystParser::_ruleNames = {
  "compileUnit", "definition", "definitionList", "nameScoped", "namespaceDefinition", 
  "structDefinition", "type", "typeList"
};

std::vector<std::string> relystParser::_literalNames = {
  "", "';'", "'.'", "'namespace'", "'{'", "'}'", "':'", "','", "", "'struct'"
};

std::vector<std::string> relystParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "COMPONENT", "STRUCT", "ID", "BLOCK_COMMENT", 
  "LINE_COMMENT", "WHITE_SPACE"
};

dfa::Vocabulary relystParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> relystParser::_tokenNames;

relystParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0xf, 0x4a, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x3, 0x2, 0x5, 0x2, 0x14, 0xa, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x1a, 0xa, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x7, 0x4, 0x1e, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x21, 0xb, 
    0x4, 0x6, 0x4, 0x23, 0xa, 0x4, 0xd, 0x4, 0xe, 0x4, 0x24, 0x3, 0x5, 0x3, 
    0x5, 0x7, 0x5, 0x29, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x2c, 0xb, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x34, 
    0xa, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x7, 0x9, 0x43, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x46, 0xb, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x2, 0x2, 0xa, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 
    0x10, 0x2, 0x3, 0x3, 0x2, 0xa, 0xb, 0x2, 0x48, 0x2, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x19, 0x3, 0x2, 0x2, 0x2, 0x6, 0x22, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x2a, 0x3, 0x2, 0x2, 0x2, 0xa, 0x2f, 0x3, 0x2, 0x2, 0x2, 0xc, 0x37, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x10, 0x44, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0x14, 0x5, 0x6, 0x4, 0x2, 0x13, 0x12, 0x3, 0x2, 
    0x2, 0x2, 0x13, 0x14, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0x15, 0x16, 0x7, 0x2, 0x2, 0x3, 0x16, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0x17, 0x1a, 0x5, 0xa, 0x6, 0x2, 0x18, 0x1a, 0x5, 0xc, 0x7, 0x2, 0x19, 
    0x17, 0x3, 0x2, 0x2, 0x2, 0x19, 0x18, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x5, 
    0x3, 0x2, 0x2, 0x2, 0x1b, 0x1f, 0x5, 0x4, 0x3, 0x2, 0x1c, 0x1e, 0x7, 
    0x3, 0x2, 0x2, 0x1d, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x21, 0x3, 0x2, 
    0x2, 0x2, 0x1f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x2, 
    0x2, 0x20, 0x23, 0x3, 0x2, 0x2, 0x2, 0x21, 0x1f, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x23, 0x24, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x22, 0x3, 0x2, 0x2, 0x2, 0x24, 0x25, 0x3, 0x2, 0x2, 0x2, 0x25, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x26, 0x27, 0x7, 0xc, 0x2, 0x2, 0x27, 0x29, 0x7, 
    0x4, 0x2, 0x2, 0x28, 0x26, 0x3, 0x2, 0x2, 0x2, 0x29, 0x2c, 0x3, 0x2, 
    0x2, 0x2, 0x2a, 0x28, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x2b, 0x3, 0x2, 0x2, 
    0x2, 0x2b, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x2a, 0x3, 0x2, 0x2, 0x2, 
    0x2d, 0x2e, 0x7, 0xc, 0x2, 0x2, 0x2e, 0x9, 0x3, 0x2, 0x2, 0x2, 0x2f, 
    0x30, 0x7, 0x5, 0x2, 0x2, 0x30, 0x31, 0x5, 0x8, 0x5, 0x2, 0x31, 0x33, 
    0x7, 0x6, 0x2, 0x2, 0x32, 0x34, 0x5, 0x6, 0x4, 0x2, 0x33, 0x32, 0x3, 
    0x2, 0x2, 0x2, 0x33, 0x34, 0x3, 0x2, 0x2, 0x2, 0x34, 0x35, 0x3, 0x2, 
    0x2, 0x2, 0x35, 0x36, 0x7, 0x7, 0x2, 0x2, 0x36, 0xb, 0x3, 0x2, 0x2, 
    0x2, 0x37, 0x38, 0x9, 0x2, 0x2, 0x2, 0x38, 0x39, 0x7, 0xc, 0x2, 0x2, 
    0x39, 0x3a, 0x7, 0x8, 0x2, 0x2, 0x3a, 0x3b, 0x5, 0x10, 0x9, 0x2, 0x3b, 
    0x3c, 0x7, 0x3, 0x2, 0x2, 0x3c, 0xd, 0x3, 0x2, 0x2, 0x2, 0x3d, 0x3e, 
    0x5, 0x8, 0x5, 0x2, 0x3e, 0xf, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x5, 
    0xe, 0x8, 0x2, 0x40, 0x41, 0x7, 0x9, 0x2, 0x2, 0x41, 0x43, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x43, 0x46, 0x3, 0x2, 0x2, 
    0x2, 0x44, 0x42, 0x3, 0x2, 0x2, 0x2, 0x44, 0x45, 0x3, 0x2, 0x2, 0x2, 
    0x45, 0x47, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 0x47, 
    0x48, 0x5, 0xe, 0x8, 0x2, 0x48, 0x11, 0x3, 0x2, 0x2, 0x2, 0x9, 0x13, 
    0x19, 0x1f, 0x24, 0x2a, 0x33, 0x44, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

relystParser::Initializer relystParser::_init;
