#pragma once
#include <rendering.hpp>
#include <game_object.hpp>
#include <resource_manager.hpp>
#include <script_manager.hpp>
#include <string>
struct ResourceManager;
namespace Aurora {
	struct Scene {
		Scene(EventManager* manager);
		~Scene();
		static void expose_to_script(ScriptManager* m);
		void init() { root.init(); }
		void render(Renderer* renderer);
		void update(double dt);
		GameObject* create_object();
		GameObject root;
		ScriptManager* mScriptManager;
	private:
		uint64_t mID;
		std::vector<GameObject*> mObjects;
		ResourceManager mManager;
		Renderer mRenderer;

	};
}
