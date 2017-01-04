#ifndef CBLOCKS_SCENE_HPP
#define CBLOCKS_SCENE_HPP
#include <rendering.hpp>
namespace CBlocks {
	struct Scene {
		Scene();
		~Scene();
		void render(const Renderer& renderer);
		void update(float dt);
	};
}
#endif // !CBLOCKS_SCENE_HPP
