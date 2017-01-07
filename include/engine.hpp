#ifndef CBLOCKS_ENGINE_HPP
#define CBLOCKS_ENGINE_HPP
#include <string>
#include <rendering.hpp>
#include <ResourceManager.h>
#include <game.hpp>
#include <events.hpp>
namespace CBlocks {
	struct Platform;
	struct Engine {
		Engine(int width, int height, const std::string& title);
		void start();
	private:
		void init();
		void run();
		bool mRunning;
		Platform* mPlatform;
		Renderer* mRenderer;
		int mWidth, mHeight;
		std::string mTitle;
		ResourceManager* mManager;
		EventManager* mEventManager;
	};
}
#endif // !CBLOCKS_ENGINE_HPP
