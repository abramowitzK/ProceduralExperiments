#ifndef CBLOCKS_GAME_OBJECT_HPP
#define CBLOCKS_GAME_OBJECT_HPP
#include <vector>
#include <component.hpp>
#include <transform.hpp>
#include <rendering.hpp>

namespace CBlocks {
	struct GameObject {
		GameObject();
		GameObject(GameObject* mParent);
		~GameObject();
		std::vector<GameObject*> mChildren;
		void update(double dt);
		void render(Renderer* renderer);
	private:
		GameObject* mParent;
		std::vector<Component> mComponents;
		Transform mTransform;
	};

}
#endif // !CBLOCKS_GAME_OBJECT_HPP
