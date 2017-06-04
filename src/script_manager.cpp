#include "script_manager.hpp"
#include <cassert>
#include <transform.hpp>
#include <game_object.hpp>
#include <sol.hpp>
#include <game.hpp>
#include <scene.hpp>
#include <events.hpp>
namespace Aurora {
	ScriptManager::ScriptManager(EventManager* manager) {
		mEvents = manager;
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
		mLuaError = false;
		mLua = new sol::state(sol::c_call<decltype(&ScriptManager::handle_lua_error), &ScriptManager::handle_lua_error>);
		mLua->open_libraries();
		Transform::expose_to_script(this);
		Game::expose_to_script(this);
		Scene::expose_to_script(this);
		Component::expose_to_script(this);
		GameObject::expose_to_script(this);
		EventManager::expose_to_script(this);
		(*mLua)["scene"] = std::ref(currentScene);
		(*mLua)["events"] = std::ref(mEvents);
	}
}