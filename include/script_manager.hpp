#pragma once
#include <sol.hpp>
#include <iostream>
#include <lua.hpp>
#include <vector>
#include <script.hpp>

namespace Aurora {
	struct Scene;
	struct ScriptManager {
		
		~ScriptManager() {
		}
		void update(double dt);
		void init(Scene* currentScene);
		sol::state* get_lua_state() { return mLua; }
		ScriptManager();
	private:
		sol::state* mLua;
		std::vector<Script> mScripts;
	};
}
