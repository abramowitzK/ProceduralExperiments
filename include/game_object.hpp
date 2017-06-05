#pragma once
#include <vector>
#include <component.hpp>
#include <transform.hpp>
#include <rendering.hpp>
#include <script.hpp>
namespace Aurora {
	struct GameObject {
		friend struct Scene;
		static void expose_to_script(ScriptManager* m);
		~GameObject();
		std::vector<GameObject*> mChildren;
		void update(double dt);
		void render(Renderer* renderer);
		void add_component(Component* comp);
		Component* get_component(ComponentType type);
		void init();
		GameObject* parent;
		Transform transform;
	private:
		uint64_t mId;
		GameObject();
		GameObject(GameObject* parent);
		std::vector<Component*> mComponents;
	};

}