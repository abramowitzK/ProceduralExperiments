#pragma once
#include <sol.hpp>
#include <iostream>
#include <lua.hpp>
#include <vector>
#include <script.hpp>

namespace Aurora {
	struct Scene;
	struct EventManager;
	struct ScriptManager {
		ScriptManager(EventManager* manager);
		~ScriptManager() {
		}
		void update(double dt);
		void load(Scene* currentScene);
		void load_error_handling(std::string errorHandlingScript);
		sol::state* get_lua_state() { return mLua; }
	private:
		void handle_lua_error(sol::optional<std::string> msg) {
			printf("Lua error\n");
			if (msg) {
				printf("%s", msg.value().c_str());
			}
			mLuaError = true;
		}
		bool mLuaError = false;
		sol::state* mLua;
		std::vector<Script> mScripts;
		EventManager* mEvents;
		std::string mErrorHandler;
	};
}
