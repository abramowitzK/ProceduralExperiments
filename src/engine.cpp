#include <engine.hpp>
#include <platform.hpp>
namespace CBlocks {
	Engine::Engine(int width, int height, const std::string & title) : mWidth(width), mHeight(height), mTitle(title), mRunning(false) {
		mPlatform = new Platform();
		mManager = ResourceManager::instance();
		mEventManager = new EventManager();
		mScriptManager = ScriptManager::instance();
		mPhysics = Physics::instance();
		
	}
	void Engine::start(const std::string& initialScene) {
		init(initialScene);
		mRunning = true;
		run();
	}

	void Engine::update(double dt) {
		mRenderer->update(dt);
		update_game(&mGame, dt);
	}
	void Engine::render() {
		render_game(&mGame, mRenderer);
	}

	void Engine::init(const std::string& initialScene) {
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

		mScriptManager->init();
		mGame.load(initialScene);
	}

	void Engine::run() {
		double current_time = mPlatform->get_time();
		double accumulator = 0;
		double t = 0;
		double dt = 0.01667;
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
				mPhysics->fixed_update(dt);
			}
			update(frame_time);
			mRenderer->clear_screen(true, true);
			render();
			mRenderer->render();
			mPlatform->swap_buffers();
			mEventManager->update_previous();
		}
	
	
	}
}