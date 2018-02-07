#pragma once
#include <string>
#include <rendering.hpp>
#include <resource_manager.hpp>
#include <game.hpp>
#include <physics.hpp>
namespace Aurora {
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
		Physics* mPhysics;
		Game mGame;
	};
}
