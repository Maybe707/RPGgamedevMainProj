#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include "Entity.h"

class LuaScript
{
private:
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

	std::string testPrint()
	{
		return "Hello from c++";
	}

	friend class LuaScriptSystem;
};

#endif

