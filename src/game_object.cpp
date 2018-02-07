#include <game_object.hpp>
#include <camera_component.hpp>
#include <rendering.hpp>
#include <component.hpp>
namespace Aurora {
	GameObject::GameObject(): parent(nullptr) {}

	GameObject::GameObject(GameObject * parent) : parent(parent) {}

	GameObject::~GameObject() {
		for (const auto& child : mChildren) {
			delete child;
		}
	}
	void GameObject::update(double dt) {
		for (const auto comp : mComponents) {
			if (comp->mType == ComponentType::Camera) {
				((CameraComponent*)comp)->update(dt);
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
			if (comp->mType == ComponentType::Camera) {
				renderer->render((CameraComponent*)comp);
			}
		}
		for (const auto& go : mChildren) {
			go->render(renderer);
		}
	}
	void GameObject::add_component(Component* comp) {
		comp->mOwner = this;
		if (!comp->mTransform)
			comp->mTransform = new Transform();
		comp->mTransform->mParent = &this->transform;
		mComponents.push_back(comp);
	}

	Component* GameObject::get_component_base(ComponentType type) {

		for (const auto comp : mComponents) {
			if (comp->mType == type) {
				return comp;
			}
		}
		return nullptr;
	}
	void GameObject::init() {
		for (const auto comp : mComponents) {
		}
		for (const auto& go : mChildren) {
			go->init();
		}
	}
}