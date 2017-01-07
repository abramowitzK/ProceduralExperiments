#include <engine.hpp>
#include <platform.hpp>
namespace CBlocks {
	Engine::Engine(int width, int height, const std::string & title) : mWidth(width), mHeight(height), mTitle(title), mRunning(false) {
		mPlatform = new Platform();
		mManager = ResourceManager::instance();
		mEventManager = new EventManager();
		
	}
	void Engine::start() {
		init();
		mRunning = true;
		run();
	}

	void Engine::init() {
		mPlatform->create_window(mTitle.c_str(), mWidth, mHeight);
		mRenderer = new Renderer(mWidth, mHeight);
		mManager->load_defaults();
		mRenderer->init_default_resources();
		mRenderer->create_camera(*mEventManager);
		std::function<void()> shutdown = [=]() { mRunning = false; };
		mEventManager->subscribe_to_argless_event(Intents::Shutdown, shutdown);
		mEventManager->subscribe_to_resize_event([=](int a, int b) {mPlatform->handle_resize(a, b); });
		mEventManager->subscribe_to_resize_event([=](int a, int b) {mPlatform->handle_resize(a, b); });
		mEventManager->subscribe_to_argless_event(Intents::Escape, [=]() {mPlatform->capture_mouse(false); });
	}

	void Engine::run() {
		double current_time = mPlatform->get_time();
		double accumulator = 0;
		double t = 0;
		double dt = 0.01;
		while (mRunning) {
			double new_time = mPlatform->get_time();
			double frame_time = new_time - current_time;
			if (frame_time > 0.25)
				frame_time = 0.25;
			current_time = new_time;
			accumulator += frame_time;
			mEventManager->poll_input();
			while (accumulator >= dt) {
				t += dt;
				accumulator -= dt;
			}
			mRenderer->update(frame_time);
			mRenderer->clear_screen(true, true);
			//scene->render(&renderer);
			mRenderer->render();
			mPlatform->swap_buffers();
			mEventManager->update_previous();
		}
	
	
	}
}