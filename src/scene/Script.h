#ifndef RPG_SCRIPT_H
#define RPG_SCRIPT_H

#include "Entity.h"

class Script
{
    Entity m_entity;
public:
    template<typename T>
    T& getComponent()
    {
        return m_entity.getComponent<T>();
    }

    Entity getEntity()
    {
        return m_entity;
    }

    friend class ScriptSystem;
};


#endif //RPG_SCRIPT_H
