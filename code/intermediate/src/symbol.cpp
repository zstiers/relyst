/*
 * Copyright (c) 2019 Zachary Stiers
 * License: https://github.com/zstiers/relyst/blob/master/LICENSE
 */

#include <intermediate/symbol.h>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...)->overloaded<Ts...>;

namespace relyst::intermediate::symbol {

struct IdentifierList {
    std::vector<std::string> result;

    void operator() (const ast::Identifier & identifier) {
        result.push_back(identifier);
    }
    void operator() (const ast::List & list) {
        for (const auto & nodePtr : list)
            std::visit(*this, nodePtr->v);
    }
    template <typename Unused>
    void operator() (const Unused &) { }
};

class ScopeNester {
    const std::size_t      m_originStackSize;
    std::vector<Scope *> & m_scopeStack;

public:
    void operator() (const ast::Identifier & identifier) {
        auto & top      = m_scopeStack.back();
        auto   existing = top->children.find(identifier);
        if (existing != top->children.end()) {
            // TODO : Replace this dynamic cast!
            m_scopeStack.push_back(dynamic_cast<Scope *>(existing->second.get()));
        }
        else {
            auto newScope = std::make_shared<Scope>();
            top->children.insert(std::make_pair(identifier, newScope));
            m_scopeStack.push_back(newScope.get());
        }
    }
    void operator() (const ast::List & list) {
        for (const auto & nodePtr : list)
            std::visit(*this, nodePtr->v);
    }
    template <typename Unused>
    void operator() (const Unused &) { }

public:
    ScopeNester (std::vector<Scope *> & scopeStack) : m_originStackSize(scopeStack.size()), m_scopeStack(scopeStack) {
    }
    ~ScopeNester () {
        m_scopeStack.erase(m_scopeStack.begin() + m_originStackSize, m_scopeStack.end());
    }
};

struct VisitorBuildStubs {
    std::vector<Scope *> scopeStack;

    void operator() (const ast::Node & node) {
        std::visit(*this, node.v);
    }
    void operator() (const ast::NodePtr & nodePtr) {
        if (nodePtr)
            operator()(*nodePtr);
    }
    void operator() (const ast::List & list) {
        for (const auto & nodePtr : list)
            Visit(nodePtr);
    }
    void operator() (const ast::Scope & scope) {
        Visit(scope.data);
    }
    void operator() (const ast::ScopeNamed & scopeNamed) {
        ScopeNester nester(scopeStack);
        std::visit(nester, scopeNamed.name->v);
        Visit<ast::Scope>(scopeNamed);
    }
    void operator() (const ast::Struct & strct) {
        auto & scope = scopeStack.back()->children;
        auto   type  = std::make_shared<Type>();
        std::visit([&scope, &type] (auto && name) {
            using T = std::decay_t<decltype(name)>;
            if constexpr (std::is_same_v<T, ast::Identifier>)
                scope.insert(std::make_pair(name, type));
        }, strct.name->v);
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

    void operator() (const ast::Node & node) {
        std::visit(*this, node.v);
    }
    void operator() (const ast::NodePtr & nodePtr) {
        if (nodePtr)
            operator()(*nodePtr);
    }
    void operator() (const ast::List & list) {
        for (const auto & nodePtr : list)
            Visit(nodePtr);
    }
    void operator() (const ast::Scope & scope) {
        Visit(scope.data);
    }
    void operator() (const ast::ScopeNamed & scopeNamed) {
        ScopeNester nester(scopeStack);
        std::visit(nester, scopeNamed.name->v);
        Visit<ast::Scope>(scopeNamed);
    }
    void operator() (const ast::Struct & strct) {
        auto & scope = scopeStack.back()->children;
        auto   type  = std::visit([&scope](auto && name) -> Type * {
            using T = std::decay_t<decltype(name)>;
            if constexpr (std::is_same_v<T, ast::Identifier>)
                return dynamic_cast<Type *>(scope.find(name)->second.get());
            return nullptr;
        }, strct.name->v);
        
        // Hard-link the base class types by finding each symbol
        std::visit([this, &type](auto && baseList) {
            using T = std::decay_t<decltype(baseList)>;
            if constexpr (std::is_same_v<T, ast::List>) {
                for (const auto & entry : baseList) {
                    IdentifierList scopedId;
                    std::visit(scopedId, entry->v);
                    type->bases.push_back(std::dynamic_pointer_cast<Type>(FindSymbol(scopedId.result)));
                }
            }
        }, strct.bases->v);
    }

    template <typename Unused>
    void operator() (const Unused &) {
    }

    template <typename T>
    void Visit (const T & t) {
        operator()(t);
    }

private:
    SymbolPtr<Base> FindSymbol (const std::vector<std::string> & scopedId) {
        if (scopedId.size() < 1)
            return nullptr;

        // Walk down the stack looking for a complete match.
        for (size_t outer = scopeStack.size(); outer-- > 0; ) {
            auto scope = scopeStack[outer];
            for (size_t inner = 0; inner < scopedId.size(); ++inner) {
                const auto found = scope->children.find(scopedId[inner]);
                if (found == scope->children.end())
                    break;
                if (inner < scopedId.size() - 1)
                    scope = dynamic_cast<Scope *>(found->second.get());
                else
                    return found->second;
            }
        }
        return nullptr;
    }
};

TableShared::TableShared (const ast::NodePtr & astRoot) {
    VisitorBuildStubs stubs;
    stubs.scopeStack.push_back(&m_globalScope);
    stubs(astRoot);

    VisitorLinkStubs link;
    link.scopeStack.push_back(&m_globalScope);
    link(astRoot);
}

} // namespace relyst::intermediate::symbol