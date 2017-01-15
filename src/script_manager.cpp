#include "script_manager.hpp"
#include <cassert>
#include <transform.hpp>
#include <game_object.hpp>
#include <sol.hpp>
#include <game.hpp>
#include <scene.hpp>
namespace CBlocks {
	ScriptManager* ScriptManager::sInstance = nullptr;
	ScriptManager::ScriptManager() {
		mLua = new sol::state();
		mLua->open_libraries();
	}
	void ScriptManager::update(double dt) {
		
	}
	void ScriptManager::init(Scene* currentScene) {
		Transform::expose_to_script();
		Game::expose_to_script();
		Scene::expose_to_script();
		Component::expose_to_script();
		GameObject::expose_to_script();
		(*mLua)["scene"] = std::ref(currentScene);
	}
}