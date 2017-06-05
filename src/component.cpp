#include <component.hpp>
#include <script_manager.hpp>
#include <game_object.hpp>
namespace Aurora {
	void Component::expose_to_script(ScriptManager* m) {
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
		l->new_enum("ComponentType",
					  "Script", ComponentType::Script,
					  "Physics", ComponentType::Physics,
					  "Mesh", ComponentType::Mesh,
					  "Camera", ComponentType::Camera,
					  "CharacterController", ComponentType::CharacterController
		);
	}
}