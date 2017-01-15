#include <component.hpp>
#include <script_manager.hpp>
#include <game_object.hpp>
namespace CBlocks {
	void Component::expose_to_script() {
	
		auto m = ScriptManager::instance();
		auto l = m->get_lua_state();
		(*l)["ComponentType"] = l->create_table_with(
			"Mesh", ComponentType::Mesh,
			"Physics", ComponentType::Physics,
			"Script", ComponentType::Script
		);
		sol::usertype<Component> type{
			"type", &Component::mType,
			"owning_object", &Component::mOwner
		};
		l->set_usertype("Component", type);
	}
}