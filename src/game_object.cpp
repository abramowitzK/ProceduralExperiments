#include "game_object.hpp"

namespace CBlocks {
	GameObject::GameObject() : parent(nullptr) {}

	GameObject::GameObject(GameObject * parent) : parent(parent){
	}

	GameObject::~GameObject() {
		for (const auto child : mChildren) {
			delete child;
		}
	}
	void GameObject::update(double dt) {}
	void GameObject::render(Renderer* renderer) {
		for (const auto& comp : mComponents) {
			if (comp.mType == ComponentType::Mesh) {
				renderer->render_mesh((Mesh*)&comp);
			}
		}
		for (const auto& go : mChildren) {
			go->render(renderer);
		}
	}
	void GameObject::add_component(Component comp) {
		mComponents.push_back(comp);
	}
}