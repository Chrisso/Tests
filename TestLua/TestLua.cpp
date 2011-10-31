// TestLua.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern "C"
{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>	
}

int _tmain(int argc, _TCHAR* argv[])
{
	_tprintf(_T("Initializing lua vm...\n"));
	lua_State *lua = lua_open();

	if (lua)
	{
		_tprintf(_T("Loading libraries...\n"));
		luaL_openlibs(lua);

		_tprintf(_T("Loading script...\n"));
		if (luaL_loadfile(lua, "D:\\Projekte\\Tests\\TestLua\\test.lua") == 0)
		{
			lua_pcall(lua, 0, LUA_MULTRET, 0);	// run main
	
			_tprintf(_T("Calling script function...\n"));
			lua_pushstring(lua, "ftest2");	
			lua_gettable(lua, LUA_GLOBALSINDEX);
			lua_pushnumber(lua, 1.0);
			if (lua_pcall(lua, 1, 1, 0) == 0)
			{
				if (lua_isnumber(lua, -1))
				{
					_tprintf(_T("Result: %f\n"), lua_tonumber(lua, -1));
				}
				lua_pop(lua, 1);
			}
			else
			{
				_tprintf(_T("Error in Script: %s\n"), lua_tostring(lua, -1));
				lua_pop(lua, 1);
			}
		}

		lua_close(lua);
	}
	else _tprintf(_T("Error initializing lua!\n"));

#ifdef _DEBUG
	_tsystem(_T("pause"));
#endif

	return 0;
}

