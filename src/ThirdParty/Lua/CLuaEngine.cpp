//
//  CLuaEngine.cpp
//
//  Base PvZ2C (arm64-v8a, 3.5.7).
//  Reconstructed by EvilHack28 on 2026-11-25.
//

#include "SexyAppFramework/Common.h"

#include "LuaEngine/CLuaEngine.h"

using namespace Lua;

/////////////// Accessors ///////////////

Sexy::ScrollWidgetListener* CLuaEngine::GetScrollWidgetListener()
{
	return this;
}

void CLuaEngine::ReloadScripts()
{
	m_needReload = true;
}

void CLuaEngine::EnableRun(bool i_enable)
{
	m_disableRun = !i_enable;
}

bool CLuaEngine::IsGameRunning()
{
	return m_updateState == 4;
}

bool CLuaEngine::CheckUpdate()
{
	m_updateState = 3;
	return true;
}

void CLuaEngine::ReUpdate()
{
	m_needReUpdate = true;
}

void CLuaEngine::OnUpdateFinish()
{
	if (m_updateState == 2)
		m_updateState = 3;
}

/////////////// Scripts ///////////////

int CLuaEngine::LoadBuffer(lua_State* L, const char* i_buffer, int i_size, const char* i_name)
{
	return luaL_loadbuffer(L, i_buffer, i_size, i_name);
}

void CLuaEngine::AddLuaLoader(lua_CFunction i_func)
{
	if (!i_func)
		return;

	lua_getglobal(m_luaState, "package");
	lua_getfield(m_luaState, -1, "loaders");
	lua_pushcfunction(m_luaState, i_func);
	for (int i = lua_objlen(m_luaState, -2) + 1; i > 2; --i)
	{
		lua_rawgeti(m_luaState, -2, i - 1);
		lua_rawseti(m_luaState, -3, i);
	}
	lua_rawseti(m_luaState, -2, 2);
	lua_setfield(m_luaState, -2, "loaders");
	lua_pop(m_luaState, 1);
}

bool CLuaEngine::ExecuteTableFunction(const char* i_tableName, const char* i_funcName)
{
	if (m_disableRun)
		return false;

	int top = lua_gettop(m_luaState);
	StackClean clean(m_luaState, top);
	lua_getglobal(m_luaState, i_tableName);
	if (!lua_istable(m_luaState, -1))
		return false;

	lua_getfield(m_luaState, -1, i_funcName);
	if (!lua_isfunction(m_luaState, -1))
		return false;

	lua_getglobal(m_luaState, i_tableName);
	if (popcap_lua_xpcall(m_luaState, 1, 0, 0) != 0)
	{
		lua_tostring(m_luaState, -1);
		return false;
	}
	return true;
}

void CLuaEngine::RemoveScriptHandler(int i_handler)
{
	toluafix_remove_function_by_refid(m_luaState, i_handler);
}
