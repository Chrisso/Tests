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
	lua_State *lua = luaL_newstate();

	if (lua)
	{
		_tprintf(_T("Loading libraries...\n"));
		luaL_openlibs(lua);

		_tprintf(_T("Loading script...\n"));
		if (luaL_loadfile(lua, "test.lua") == 0)
		{
			lua_pcall(lua, 0, LUA_MULTRET, 0);	// run main

			//_tprintf(_T("Stack height: %d\n"), lua_gettop(lua));
			_tprintf(_T("Calling script function...\n"));
			lua_pushglobaltable(lua);
			lua_pushstring(lua, "ftest2"); // function name
			lua_gettable(lua, -2);         // ... converted to function
			lua_pushnumber(lua, 1.0);      // argument
			if (lua_pcall(lua, 1, 1, 0) == 0)
			{
				if (lua_isnumber(lua, -1))
				{
					_tprintf(_T("Result: %f\n"), lua_tonumber(lua, -1));
				}
				lua_pop(lua, 2); // clear return value and global table
			}
			else
			{
#ifdef UNICODE
				WCHAR szMsg[255];
				::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, lua_tostring(lua, -1), -1, szMsg, 255);
				_tprintf(_T("Error in Script: %s\n"), szMsg);
#else
				_tprintf(_T("Error in Script: %s\n"), lua_tostring(lua, -1));
#endif
				lua_pop(lua, 2); // clear error and global table
			}
			//_tprintf(_T("Stack height: %d\n"), lua_gettop(lua));
		}

		lua_close(lua);
	}
	else _tprintf(_T("Error initializing lua!\n"));

#ifdef _DEBUG
	_tsystem(_T("pause"));
#endif

	return 0;
}

