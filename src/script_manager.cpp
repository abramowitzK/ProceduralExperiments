#include "script_manager.hpp"
#include <cassert>
#include <transform.hpp>
#include <game_object.hpp>
#include <sol.hpp>
#include <game.hpp>
#include <scene.hpp>
namespace Aurora {
	ScriptManager::ScriptManager() {
		mLua = new sol::state();
		mLua->open_libraries();
	}
	void ScriptManager::update(double dt) {
		
	}
	void ScriptManager::init(Scene* currentScene) {
		Transform::expose_to_script(this);
		Game::expose_to_script(this);
		Scene::expose_to_script(this);
		Component::expose_to_script(this);
		GameObject::expose_to_script(this);
		(*mLua)["scene"] = std::ref(currentScene);
	}
}