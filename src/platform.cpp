#include <platform.hpp>
namespace Aurora {
	Platform::Platform() {
		SDL_Init(SDL_INIT_EVERYTHING);
		mFreq = static_cast<double>(SDL_GetPerformanceFrequency());
		mStart = SDL_GetPerformanceCounter();
	}

	Platform::~Platform() {
		SDL_DestroyWindow(mWindowHandle);
		SDL_GL_DeleteContext(mContext);
		SDL_Quit();
	}

	void Platform::create_window(const char * title, int width, int height) {
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetSwapInterval(0);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		mWindowHandle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		mContext = SDL_GL_CreateContext(mWindowHandle);
		//SDL_SetWindowFullscreen(mWindowHandle, SDL_WINDOW_FULLSCREEN_DESKTOP);
		//SDL_SetWindowSize(mWindowHandle,1920,1080);
	}

	void Platform::handle_resize(int width, int height) {
		printf("Resizing to %d, %d\n", width, height);
	}

	double Platform::get_time() {
		return static_cast<double>(SDL_GetPerformanceCounter() - mStart) / mFreq;
	}

	void Platform::swap_buffers() {
		SDL_GL_SwapWindow(mWindowHandle);
	}

	void Platform::capture_mouse(bool capture) {
		if (capture)
			SDL_SetRelativeMouseMode(SDL_TRUE);
		else
			SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}