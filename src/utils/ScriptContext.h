#ifndef SCRIPTCONTEXT_H
#define SCRIPTCONTEXT_H

#include <limits>
#include <cstdio>
#include <sol/sol.hpp>
#include <string>
#include <utility>

class ScriptContext
{
private:
	sol::state m_luaState;
	std::string m_currentTable;
public:
	ScriptContext();

	void setCurrentScript(const std::string &name);

	template<typename... Args>
	void callFunction(const std::string &method, Args&&... args);

	template<typename Class, typename... Args>
	void addType(const std::string &method, Args&&... args);

	void reset();

	void collectGarbage();

private:
	void init(const std::string &path);
	friend class LuaScriptSystem;
};

template<typename... Args>
void ScriptContext::callFunction(const std::string &method, Args&&... args)
{
	sol::function func = m_luaState[m_currentTable][method];
	sol::function_result res = func(m_luaState[m_currentTable], std::forward<Args>(args)...);
	if (!res.valid())
	{
		sol::error R = res;
		//fprintf(stderr, "[WARN] Error runing lua %s function %s: %s\n", m_currentTable.c_str(), method.c_str(), R.what());
	}
}

template<typename Class, typename... Args>
void ScriptContext::addType(const std::string &name, Args&&... args)
{
	m_luaState.new_usertype<Class>(name, std::forward<Args>(args)...);
}


#endif

