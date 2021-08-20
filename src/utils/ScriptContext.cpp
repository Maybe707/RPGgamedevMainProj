#include "ScriptContext.h"

ScriptContext::ScriptContext() : m_luaState() { }

void ScriptContext::setCurrentScript(const  std::string &name)
{
	m_currentTable = name;
}

void ScriptContext::collectGarbage()
{
	m_luaState.collect_garbage();
}

void ScriptContext::reset()
{
	m_currentTable.clear();
}

void ScriptContext::init(const std::string &path)
{	
	m_luaState[m_currentTable] = m_luaState.require_file(m_currentTable, path);
}

