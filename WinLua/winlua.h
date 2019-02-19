#ifndef WINLUA_H_V1
#define WINLUA_H_V1
#include <Windows.h>
#include <string>
#include <vector>

/* Include ImGui */
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_dx11.h"

/* Include Lua */
extern "C" {
#include "../Lua/lua.h"
#include "../Lua/lauxlib.h"
}

struct library {
	std::string name;
	std::vector<std::pair<lua_CFunction, std::string>> imports;

	library() {
		this->name = std::string();
		this->imports = std::vector<std::pair<lua_CFunction, std::string>>();
	}

	library(std::string name) {
		this->name = name;
		this->imports = std::vector<std::pair<lua_CFunction, std::string>>();
	}

	void register_function(std::string name, lua_CFunction function) {
		imports.push_back(std::make_pair(function, name));
	}
};

struct imgui_form {

};

struct winapi_form {

};

struct control {

};

class WinLua {
private:
	std::vector<library*> imported_libs;
	lua_State* g_L;
public:
	/* Library Importing */
	void import_library(library* lib) {
		imported_libs.push_back(lib);
	}

	library* create_library(std::string name) {
		library* lib = new library(name);
		return lib;
	}

	/* Lua C++ Functions */
	int library_import(lua_State* L) {
		if (lua_gettop(L) > 1)
			return luaL_error(L, "expected 1 argument");
		if (lua_type(L, 1) != LUA_TSTRING)
			return luaL_error(L, "expected a string (1)");

		std::string lib_name = lua_tostring(L, 1);
		bool got_library = false;
		library* lib;

		for (int i = 0; i < imported_libs.size(); i++) {
			library* flib = imported_libs[i];
			if (lib->name == lib_name) {
				got_library = true;
				lib = flib;
				break;
			}
		}

		if (!got_library)
			return luaL_error(L, "not a valid library to import");

		for (int i = 0; i < lib->imports.size(); i++) {
			std::pair<lua_CFunction, std::string> imp = lib->imports[i];

			lua_pushcfunction(L, imp.first);
			lua_setglobal(L, imp.second.c_str());
		}

		return 0;
	}
};

WinLua* winlua = new WinLua();
#endif