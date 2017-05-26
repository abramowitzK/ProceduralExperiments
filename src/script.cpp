#include "script.hpp"
#include <script_manager.hpp>
#include <game_object.hpp>
namespace Aurora {
	Script::Script(const std::string& tableName, std::string script, ScriptManager* m) : mScript(std::move(script)){
		mType = ComponentType::Script;
		m->get_lua_state()->script(mScript);
		self = (*(m->get_lua_state()))[std::string(tableName)];
	}
	void Script::init() {
		//All scripts are components that need access to their owning game object
		self["this"] = std::ref(mOwner);

	}
	void Script::update(double dt) {
		self["update"](self, dt);
	}

}