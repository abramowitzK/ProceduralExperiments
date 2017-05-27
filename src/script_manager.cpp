#include "script_manager.hpp"
#include <cassert>
#include <transform.hpp>
#include <game_object.hpp>
#include <sol.hpp>
#include <game.hpp>
#include <scene.hpp>
namespace Aurora {
	ScriptManager::ScriptManager() {
		mLua = nullptr;
	}
	void ScriptManager::update(double dt) {
		if (!mLuaError) {
			for (auto& script: mScripts) {
				script.update(dt);
			}
		}
	}
	void ScriptManager::load(Scene* currentScene) {
		if(mLua) delete mLua;
		mLua = new sol::state(sol::c_call<decltype(&ScriptManager::handle_lua_error), &ScriptManager::handle_lua_error>);
		mLua->open_libraries();
		Transform::expose_to_script(this);
		Game::expose_to_script(this);
		Scene::expose_to_script(this);
		Component::expose_to_script(this);
		GameObject::expose_to_script(this);
		(*mLua)["scene"] = std::ref(currentScene);
	}
}