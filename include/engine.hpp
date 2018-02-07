#pragma once
#include <string>
#include <game.hpp>
namespace Aurora {
	struct Platform;
	struct Renderer;
	struct ResourceManager;
	struct Physics;

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
		Physics* mPhysics;
		Game mGame;
	};
}
