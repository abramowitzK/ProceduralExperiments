#ifndef CBLOCKS_GAME_HPP
#define CBLOCKS_GAME_HPP
#include <scene.hpp>
namespace CBlocks {
	enum class GameState {
		Menu,
		Loading,
		InGame
	};
	struct Game {
		Scene* current_scene;
		GameState current_state;
		void load(const std::string& initialScene);
	};
	void update_game(Game* game, double dt);
	void render_game(Game* game, Renderer* renderer);
}
#endif // !CBLOCKS_ENGINE_HPP
