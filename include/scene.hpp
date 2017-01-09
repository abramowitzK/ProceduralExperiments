#ifndef CBLOCKS_SCENE_HPP
#define CBLOCKS_SCENE_HPP
#include <rendering.hpp>
#include <game_object.hpp>
#include <string>
namespace CBlocks {
	struct Scene {
		Scene();
		~Scene();
		static void expose_to_script();
		void init() { root.init(); }
		void render(Renderer* renderer);
		void update(double dt);
		GameObject* create_object();
		GameObject root;
	private:
		uint64_t mID;
		std::vector<GameObject*> mObjects;
	};
}
#endif // !CBLOCKS_SCENE_HPP
