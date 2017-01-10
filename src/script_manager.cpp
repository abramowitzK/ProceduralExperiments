#include "script_manager.hpp"
#include <cassert>
#include <transform.hpp>
#include <game_object.hpp>
#include <sol.hpp>
namespace CBlocks {
	ScriptManager* ScriptManager::sInstance = nullptr;
	ScriptManager::ScriptManager() {
		mLua = new sol::state();
		mLua->open_libraries();
	}
	void ScriptManager::update(double dt) {
		
	}
	void ScriptManager::init() {
		Transform::expose_to_script();
		mLua->new_usertype<GameObject>("GameObject",
			"transform",
			sol::property(&GameObject::transform, &GameObject::transform)
			);
	}
}