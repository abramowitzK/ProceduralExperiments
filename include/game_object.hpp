#ifndef CBLOCKS_GAME_OBJECT_HPP
#define CBLOCKS_GAME_OBJECT_HPP
#include <vector>
#include <component.hpp>
#include <transform.hpp>

namespace CBlocks {
	struct GameObject {
		GameObject();
		GameObject(GameObject* mParent);
		~GameObject();
	private:
		GameObject* mParent;
		std::vector<GameObject*> mChildren;
		std::vector<Component> mComponents;
	};
	Transform mTransform;
}
#endif // !CBLOCKS_GAME_OBJECT_HPP
