/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#include <script/script.h>
#include "ast_builder_visitor.h"
#include "generated/relystLexer.h"
#include "generated/relystParser.h"

#include <antlr4/antlr4-runtime.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/ostreamwrapper.h>
#include <iostream>

#include <intermediate/symbol.h>

namespace relyst::script {

using namespace relyst::intermediate;

template <typename W>
struct JsonTo {
    W & writer;

    void operator() (const ast::Node & node) {
        writer.StartObject();
        if (auto * debugInfo = node.GetDebugInfo())
            AddMemberObject("!debugInfo", *debugInfo);
        std::visit(*this, node.v);
        writer.EndObject();
    }
    void operator() (const ast::NodePtr & nodePtr) {
        if (nodePtr)
            operator()(*nodePtr);
        else
            writer.Null();
    }
    void operator() (const ast::DebugInfo & debugInfo) {
        AddMemberObject("sourceStart", debugInfo.sourceStart);
        AddMemberObject("sourceStop",  debugInfo.sourceStop);
    }
    void operator() (const ast::SourceLocation & sourceLoc) {
        writer.Key("line");
        writer.Uint64(sourceLoc.line);
        writer.Key("chPos");
        writer.Uint64(sourceLoc.positionOnLine);
    }
    void operator() (const ast::BinaryExpression & bin) {
    }
    void operator() (const ast::Identifier & id) {
        writer.Key("data");
        writer.String(id.c_str(), id.length());
    }
    void operator() (const ast::List & list) {
        writer.Key("data");
        writer.StartArray();
        for (const auto & item : list)
            VisitSpecific(item);
        writer.EndArray();
    }
    void operator() (const ast::Scope & scope) {
        AddMemberNode("data", scope.data);
    }
    void operator() (const ast::ScopeNamed & scopeNamed) {
        VisitSpecific<ast::Scope>(scopeNamed);
        AddMemberNode("name", scopeNamed.name);
    }
    void operator() (const ast::Struct & strct) {
        AddMemberNode("name", strct.name);
        AddMemberNode("bases", strct.bases);
    }
    void operator() (const ast::UnaryExpression & bin) {

    }
    template <typename Unhandled>
    void operator() (const Unhandled &) {
    }

private:
    void AddMemberNode (const char * name, const ast::NodePtr & nodePtr) {
        writer.Key(name);
        VisitSpecific(nodePtr);
    }
    template <typename T>
    void AddMemberObject (const char * name, const T & t) {
        writer.Key(name);
        writer.StartObject();
        VisitSpecific(t);
        writer.EndObject();
    }
    template <typename T>
    void VisitSpecific (const T & t) {
        operator()(t);
    }
};

void Parse (const std::string_view & text) {
    antlr4::ANTLRInputStream input(text.data(), text.length());
    relystLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    relystParser parser(&tokens);

    AstBuilderVisitor visitor;
    auto rootNode = visitor.Visit(parser.compileUnit());

    //rapidjson::OStreamWrapper ostream(std::cout);
    //rapidjson::PrettyWriter writer(ostream);
    //JsonTo<decltype(writer)>{ writer }(rootNode);

    intermediate::symbol::TableShared sharedTable(rootNode);
}

} // relyst::script