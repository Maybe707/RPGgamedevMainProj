#include <memory>
#include "LuaScriptSystem.h"
#include "../components/LuaScriptComponent.h"
#include "../components/NameComponent.h"
#include "../../utils/OpenSimplexNoise.h"

LuaScriptSystem::LuaScriptSystem(entt::registry &registry) 
	: m_registry(registry),
	  m_ctx()
{
	m_ctx.m_luaState.open_libraries(sol::lib::base, sol::lib::math, sol::lib::string);
	m_ctx.addType<Entity>("Entity");
	m_ctx.addType<LuaScript>("LuaScript",
			"getEntity", &LuaScript::getEntity,
			"testPrint", &LuaScript::testPrint,
			"getNameComponent", &LuaScript::getComponent<NameComponent>);
	m_ctx.addType<OpenSimplexNoise>("OpenSimplexNoise", sol::constructors<OpenSimplexNoise(), OpenSimplexNoise(unsigned int)>(),
			"seed", sol::property(&OpenSimplexNoise::getSeed, &OpenSimplexNoise::setSeed),
			"octaves", sol::property(&OpenSimplexNoise::getOctaves, &OpenSimplexNoise::setOctaves),
			"lacunarity", sol::property(&OpenSimplexNoise::getLacunarity, &OpenSimplexNoise::setLacunarity),
			"persistence", sol::property(&OpenSimplexNoise::getPersistence, &OpenSimplexNoise::setPersistence),
			"period", sol::property(&OpenSimplexNoise::getPeriod, &OpenSimplexNoise::setPeriod),
			"getNoise", &OpenSimplexNoise::getNoise);
	m_ctx.addType<NameComponent>("NameComponent", "name", &NameComponent::name);
}

void LuaScriptSystem::update(float deltaTime)
{
	auto view = m_registry.view<LuaScriptComponent>();
	for (auto entity : view)
	{
		auto &luaScriptComponent = view.get<LuaScriptComponent>(entity);
		m_ctx.setCurrentScript(luaScriptComponent.scriptName);
		if (!luaScriptComponent.instance)
		{
			luaScriptComponent.instance = std::make_shared<LuaScript>();
			luaScriptComponent.instance->m_entity = { entity, &m_registry };
			m_ctx.init(luaScriptComponent.scriptPath);
			m_ctx.m_luaState[m_ctx.m_currentTable]["instance"] = luaScriptComponent.instance;

			m_ctx.callFunction("init");
		}
		m_ctx.callFunction("update", deltaTime);

		m_ctx.reset();
	}
}

void LuaScriptSystem::destroyScript()
{
	
}

void LuaScriptSystem::destroy()
{
	
}

