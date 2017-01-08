#ifndef CBLOCKS_SCRIPT_MANAGER_HPP
#define CBLOCKS_SCRIPT_MANAGER_HPP
#include <sol.hpp>
#include <iostream>
#include <lua.hpp>
#include <vector>
#include <script.hpp>
namespace CBlocks {
	struct ScriptManager {
		
		~ScriptManager() {
		}
		void update(double dt);
		void init();
		static ScriptManager* instance() {
			if (!s_instance) {
				s_instance = new ScriptManager();
			}
			return s_instance;
		}
		sol::state* get_lua_state() { return mLua; }
	private:
		ScriptManager();
		static ScriptManager* s_instance;
		sol::state* mLua;
		std::vector<Script*> mScripts;
	};
}
#endif