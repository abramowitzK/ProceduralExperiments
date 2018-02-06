#include <game.hpp>
#include <resource_manager.hpp>
namespace Aurora {
	void update_game(Game * game, double dt) {
		game->current_scene->update(dt);
	}

	void render_game(Game * game, Renderer * renderer) {
		game->current_scene->render(renderer);
	}
	void Game::load(const std::string & initialScene, EventManager* events) {
		auto manager = ResourceManager::instance();
		current_scene = manager->load_scene(initialScene, events);
		current_scene->init();
	}
}