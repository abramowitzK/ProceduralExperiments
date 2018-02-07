#include "scene.hpp"
namespace Aurora {

Scene::Scene() {}
Scene::~Scene() {}

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
    mObjects.push_back(new GameObject());
    auto o = mObjects.back();
    o->mId = mID++;
    return o;
}
} // namespace Aurora
