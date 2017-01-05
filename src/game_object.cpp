#include "game_object.hpp"

namespace CBlocks {
	GameObject::GameObject() : mParent(nullptr) {}

	GameObject::GameObject(GameObject * parent) : mParent(parent){
	}

	GameObject::~GameObject() {
		for (const auto child : mChildren) {
			delete child;
		}
	}
	void GameObject::update(double dt) {}
	void GameObject::render(Renderer * renderer) {
		for (const auto& comp : mComponents) {
			if (comp.mType == ComponentType::Mesh) {
				renderer->render_mesh((Mesh*)&comp);
			}
		}
		for (const auto& go : mChildren) {
			go->render(renderer);
		}
	}
}