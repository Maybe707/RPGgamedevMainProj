#ifndef LUASCRIPTCOMPONENT_H
#define LUASCRIPTCOMPONENT_H

#include <string>
#include <memory>
#include "../LuaScript.h"

struct LuaScriptComponent
{
	std::shared_ptr<LuaScript> instance;	

	std::string scriptName;
	std::string scriptPath;
};

#endif

