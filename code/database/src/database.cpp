#include <database/database.h>

namespace relyst::database {

void AddComponent (Surrogate surrogate, ComponentKey componentKey) {

}

Surrogate Database::CreateRow () {
    return m_nextRow++;
}

} // relyst::database