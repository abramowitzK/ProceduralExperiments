#ifndef CBLOCKS_SCENE_HPP
#define CBLOCKS_SCENE_HPP
#include <rendering.hpp>
#include <game_object.hpp>
#include <string>
namespace CBlocks {
	struct Scene {
		Scene();
		~Scene();
		void render(Renderer* renderer);
		void update(double dt);
	private:
		GameObject* mRoot;

	};
}
#endif // !CBLOCKS_SCENE_HPP
