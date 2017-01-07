#ifndef CBLOCKS_GAME_OBJECT_HPP
#define CBLOCKS_GAME_OBJECT_HPP
#include <vector>
#include <component.hpp>
#include <transform.hpp>
#include <rendering.hpp>
#include <script.hpp>
namespace CBlocks {
	struct GameObject {
		friend struct Scene;
		~GameObject();
		std::vector<GameObject*> mChildren;
		void update(double dt);
		void render(Renderer* renderer);
		void add_component(Component* comp);
		GameObject* parent;
		Transform transform;
		Script* script;
	private:
		GameObject();
		GameObject(GameObject* parent);
		std::vector<Component*> mComponents;
	};

}
#endif // !CBLOCKS_GAME_OBJECT_HPP
