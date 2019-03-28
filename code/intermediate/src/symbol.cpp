/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#include <intermediate/symbol.h>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;

namespace relyst::intermediate::symbol {

class ScopeNester {
    const std::size_t      m_originStackSize;
    std::vector<Scope *> & m_scopeStack;

public:
    ScopeNester (std::vector<Scope *> & scopeStack, const std::string_view & name) : m_originStackSize(scopeStack.size()), m_scopeStack(scopeStack) {
        if (name.empty())
            return;
        auto & top = scopeStack.back();
        auto   id = std::string(name);
        auto   existing = top->children.find(id);
        if (existing != top->children.end()) {
            // TODO : Get rid of this dynamic cast
            scopeStack.push_back(dynamic_cast<Scope *>(existing->second.get()));
        }
        else {
            auto newScope = std::make_shared<Scope>();
            top->children.insert(std::make_pair(id, newScope));
            scopeStack.push_back(newScope.get());
        }
    }
    ~ScopeNester () {
        m_scopeStack.erase(m_scopeStack.begin() + m_originStackSize, m_scopeStack.end());
    }
};

struct VisitorBuildStubs {
    std::vector<Scope *> scopeStack;

    void operator() (const ast::Node * nodePtr) {
        if (nodePtr)
            ast::Visit(*this, *nodePtr);
    }
    void operator() (const ast::Scope & node) {
        ScopeNester nester(scopeStack, node.name);
        for (const auto * child : node.children)
            ast::Visit(*this, *child);
    }
    void operator() (const ast::Type & node) {
        auto   type  = std::make_shared<Type>();
        auto   id    = std::string(node.name);
        scopeStack.back()->children.insert(std::make_pair(id, type));
    }

    template <typename Unused>
    void operator() (const Unused &) {
    }

    template <typename T>
    void Visit (const T & t) {
        operator()(t);
    }
};

struct VisitorLinkStubs {
    std::vector<Scope *> scopeStack;

    void operator() (const ast::Node * nodePtr) {
        if (nodePtr)
            ast::Visit(*this, *nodePtr);
    }
    void operator() (const ast::Scope & node) {
        ScopeNester nester(scopeStack, node.name);
        for (const auto * child : node.children)
            ast::Visit(*this, *child);
    }
    void operator() (const ast::Type & node) {
        // TODO : Get rid of dynamic cast
        auto id   = std::string(node.name);
        auto type = dynamic_cast<Type *>(scopeStack.back()->children.find(id)->second.get());

        for (const auto & base : node.bases)
            type->bases.push_back(std::dynamic_pointer_cast<Type>(FindSymbol(base)));
    }

    template <typename Unused>
    void operator() (const Unused &) {
    }

    template <typename T>
    void Visit (const T & t) {
        operator()(t);
    }

private:
    SymbolPtr<Base> FindSymbol (const ast::IdentifierScoped & scopedId) {
        // Walk down the stack looking for a complete match.
        for (size_t outer = scopeStack.size(); outer-- > 0; ) {
            auto scope = scopeStack[outer];
            for (auto curr = scopedId.begin(), end = scopedId.end(); curr != end; ++curr) {
                const auto found = scope->children.find(std::string(*curr));
                if (found == scope->children.end())
                    break;
                if (curr + 1 < end)
                    scope = dynamic_cast<Scope *>(found->second.get());
                else
                    return found->second;
            }
        }
        return nullptr;
    }
};

TableShared::TableShared (const ast::Node * astRoot) {
    VisitorBuildStubs stubs;
    stubs.scopeStack.push_back(&m_globalScope);
    stubs(astRoot);

    VisitorLinkStubs link;
    link.scopeStack.push_back(&m_globalScope);
    link(astRoot);
}

} // namespace relyst::intermediate::symbol