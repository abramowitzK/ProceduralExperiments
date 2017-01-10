#ifndef CBLOCKS_ENGINE_HPP
#define CBLOCKS_ENGINE_HPP
#include <string>
#include <rendering.hpp>
#include <resource_manager.hpp>
#include <game.hpp>
#include <events.hpp>
#include <script_manager.hpp>
#include <physics.hpp>
namespace CBlocks {
	struct Platform;
	struct Engine {
		Engine(int width, int height, const std::string& title);
		void start(const std::string& initialScene);
	private:
		void update(double dt);
		void render();
		void init(const std::string& initialScene);
		void run();

		bool mRunning;
		int mWidth, mHeight;
		std::string mTitle;

		Platform* mPlatform;
		Renderer* mRenderer;
		ResourceManager* mManager;
		EventManager* mEventManager;
		ScriptManager* mScriptManager;
		Physics* mPhysics;
		Game mGame;
	};
}
#endif // !CBLOCKS_ENGINE_HPP
