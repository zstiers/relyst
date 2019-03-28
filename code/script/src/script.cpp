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
#include <chrono>

#include <intermediate/symbol.h>
#include <memory/allocator_linear.h>
#include <memory/size.h>

namespace relyst::script {

void Parse (const std::string_view & text) {
    auto clock = std::chrono::high_resolution_clock::now();
    auto nextProfile = [&clock](const char * msg) {
        const auto elapsed = std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - clock).count();
        std::cout << msg << ": " << elapsed << '\n';
        clock = std::chrono::high_resolution_clock::now();
    };

    antlr4::ANTLRInputStream input(text.data(), text.length());
    nextProfile("Input");
    relystLexer lexer(&input);
    nextProfile("Lexer");
    antlr4::CommonTokenStream tokens(&lexer);
    nextProfile("Tokens");
    relystParser parser(&tokens);
    nextProfile("Parser");

    std::vector<char> treeBuffer(0.1_GiB);
    memory::AllocatorLinear treeAlloc(treeBuffer.data(), treeBuffer.data() + treeBuffer.size());
    std::vector<char> stringBuffer(0.1_GiB);
    memory::AllocatorLinear stringAlloc(stringBuffer.data(), stringBuffer.data() + stringBuffer.size());
    nextProfile("Alloc");

    AstBuilderVisitor visitor(treeAlloc, stringAlloc);
    ast::Node * rootNode;
    visitor.Visit(parser.compileUnit(), rootNode);
    nextProfile("Visit");

    intermediate::symbol::TableShared table(rootNode);
    nextProfile("Global Table");

    std::cout << "Used memory (string): " << (stringBuffer.size() - stringAlloc.GetRemainingBytes(1)) << " bytes\n";
    std::cout << "Used memory (tree):   " << (treeBuffer.size() - treeAlloc.GetRemainingBytes(1)) << " bytes\n";
}

} // relyst::script