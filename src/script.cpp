#include "script.hpp"
#include <script_manager.hpp>
#include <game_object.hpp>
namespace Aurora {
	Script::Script(const std::string& tableName, std::string script, ScriptManager* m) : mScript(std::move(script)){
		mType = ComponentType::Script;
		m->get_lua_state()->script(mScript);
			//auto res = m->get_lua_state()->load(mScript);
		self = (*(m->get_lua_state()))[std::string(tableName)];
		global_state = m->get_lua_state();

	}
	void Script::init() {
		//All scripts are components that need access to their owning game object
		self["this"] = std::ref(mOwner);

	}
	void Script::update(double dt) {
		if (!valid) {
			return;
		}
		sol::protected_function func = self["update"];
		func.error_handler = (*global_state)["print_lua_error"];
		auto ret = func(self, dt);
		if (!ret.valid()) {
			valid = false;
			sol::error err = ret;
			printf("%s", err.what());
		}

	}

}