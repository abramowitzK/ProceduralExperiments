#include "script.hpp"
#include <script_manager.hpp>
#include <game_object.hpp>
namespace CBlocks {
	Script::Script(const std::string& tableName, std::string script) : mScript(std::move(script)){
		auto m = ScriptManager::instance();
		mType = ComponentType::Script;
		m->get_lua_state()->script(mScript);
		self = (*(m->get_lua_state()))[std::string(tableName)];
	}
	void Script::init() {
		self["owner"] = std::ref(owner);
		//self["owner"]["transform"] = std::ref(owner->transform);
	}
	void Script::update(double dt) {
		self["update"](self, dt);
	}

}