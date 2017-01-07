#include <game.hpp>
#include <ResourceManager.h>
namespace CBlocks {
	void update_game(Game * game, double dt) {
		game->current_scene->update(dt);
	}

	void render_game(Game * game, Renderer * renderer) {
		game->current_scene->render(renderer);
	}
	void Game::load(const std::string & initialScene) {
		auto manager = ResourceManager::instance();
		current_scene = manager->LoadScene(initialScene);
	}
}