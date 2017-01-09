#include "scene.hpp"
namespace CBlocks {

	Scene::Scene() {}
	Scene::~Scene() {}

	void Scene::expose_to_script() {
		auto m = ScriptManager::instance();
		auto l = m->get_lua_state();
		sol::usertype<Scene> type{
			"create_object", &Scene::create_object,
		};
		l->set_usertype("Scene", type);
	}

	void Scene::render(Renderer* renderer) {
		for (const auto& o : root.mChildren) {
			o->render(renderer);
		}
	}

	void Scene::update(double dt) {
		for (const auto& o : root.mChildren) {
			o->update(dt);
		}
	}

	GameObject* Scene::create_object() {
		mObjects.push_back( new GameObject());
		auto o = mObjects.back();
		o->mId = mID++;
		return o;
	}
}