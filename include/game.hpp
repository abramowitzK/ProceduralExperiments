#pragma once
#include <scene.hpp>
namespace Aurora {
	enum class GameState {
		Menu,
		Loading,
		InGame
	};
	struct Game {
		static void expose_to_script(ScriptManager* m);
		Scene* current_scene;
		GameState current_state;
		void load(const std::string& initialScene);
	};
	void update_game(Game* game, double dt);
	void render_game(Game* game, Renderer* renderer);
}
