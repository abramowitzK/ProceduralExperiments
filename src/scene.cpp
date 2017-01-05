#include "scene.hpp"
namespace CBlocks {

	Scene::Scene() {}
	Scene::~Scene() {}

	void Scene::render(Renderer* renderer) {
		for (const auto& o : mRoot->mChildren) {
			o->render(renderer);
		}
	}

	void Scene::update(double dt) {
		for (const auto& o : mRoot->mChildren) {
			o->update(dt);
		}
	}

}