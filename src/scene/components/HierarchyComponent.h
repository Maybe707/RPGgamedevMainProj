#ifndef RPG_HIERARCHYCOMPONENT_H
#define RPG_HIERARCHYCOMPONENT_H

#include "../Entity.h"

struct HierarchyComponent
{
    std::size_t children{}; // Количество детей у текущего энтити
    Entity firstChild{}; // Первый ребенок у текущего энтити
    Entity prev{}; // Предыдущий ребенок у родителя
    Entity next{}; // Следующий ребенок у родителя
    Entity parent{}; // Родительский энтити
};

#endif //RPG_HIERARCHYCOMPONENT_H
