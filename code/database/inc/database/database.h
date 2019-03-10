#include "component.h"
#include "surrogate.h"

#include <any>
#include <map>
#include <memory>

namespace relyst::database {

class Database {
public:
    Surrogate CreateRow ();

private: // Fake stuff
    struct FakeTableBase { virtual ~FakeTableBase () = 0 { } };
    template <typename T>
    struct FakeTable : FakeTableBase { std::map<Surrogate, T> data; };

    Surrogate m_nextRow = 1;
    std::map<ComponentKey, std::unique_ptr<FakeTableBase>> m_falseDb;

public: // More fake stuff
    template <typename T>
    void AddComponent (Surrogate surrogate, const T & value) {
        auto & table = FindOrCreateTable<T>();
        table.data.insert_or_assign(surrogate, value);
    }
    template <typename T>
    void RemoveComponent (Surrogate surrogate) {
        auto & table = FindOrCreateTable<T>();
        table.data.erase(surrogate);
    }

private:
    template <typename T>
    FakeTable<T> & FindOrCreateTable () {
        auto iter = m_falseDb.find(T::ComponentKey);
        if (iter == m_falseDb.end())
            iter = m_falseDb.emplace(T::ComponentKey, new FakeTable<T>).first;
        return *static_cast<FakeTable<T> *>(iter->second.get());
    }
};

} // relyst::database