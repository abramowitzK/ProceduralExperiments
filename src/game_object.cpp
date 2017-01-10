#include "game_object.hpp"
#include <rigid_body.hpp>
namespace CBlocks {
	GameObject::GameObject() : parent(nullptr) {}

	GameObject::GameObject(GameObject * parent) : parent(parent){
	}

	GameObject::~GameObject() {
	}
	void GameObject::update(double dt) {
		for (const auto comp : mComponents) {
			if (comp->mType == ComponentType::Script) {
				((Script*)comp)->update(dt);
			}
			if (comp->mType == ComponentType::Physics) {
				((RigidBody*)comp)->update(dt);
			}
		}
		for (const auto& go : mChildren) {
			go->update(dt);
		}
	}
	void GameObject::render(Renderer* renderer) {
		for (const auto comp : mComponents) {
			if (comp->mType == ComponentType::Mesh) {
				renderer->render_mesh((MeshRenderer*)comp);
			}
			if (comp->mType == ComponentType::Script) {
				static_cast<Script*>(comp)->render(renderer);
			}
		}
		for (const auto& go : mChildren) {
			go->render(renderer);
		}
	}
	void GameObject::add_component(Component* comp) {
		mComponents.push_back(comp);
	}
	void GameObject::init() {
		for (const auto comp : mComponents) {
			if (comp->mType == ComponentType::Script) {
				static_cast<Script*>(comp)->init();
			}
		}
		for (const auto& go : mChildren) {
			go->init();
		}
	}
}