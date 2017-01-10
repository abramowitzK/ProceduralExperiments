#include <game.hpp>
#include <ResourceManager.h>
#include <script_manager.hpp>
namespace CBlocks {
	void update_game(Game * game, double dt) {
		game->current_scene->update(dt);
	}

	void render_game(Game * game, Renderer * renderer) {
		game->current_scene->render(renderer);
	}
	void Game::expose_to_script() {
		auto manager = ScriptManager::instance();
		auto l = manager->get_lua_state();
	}
	void Game::load(const std::string & initialScene) {
		auto manager = ResourceManager::instance();
		current_scene = manager->LoadScene(initialScene);
		current_scene->init();
	}
}