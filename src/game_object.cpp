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
}