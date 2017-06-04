#pragma once

#include <SDL2\SDL.h>
#include <SDL2\SDL_filesystem.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <type_traits>
namespace Aurora {
	/**
	 * Platform layer state
	 * TODO: Should handle:
	 * 		-FileIO
	 * 		-Opening windows : Done
	 * 		-Sound?
	 * 		-Keep thinking...
	 */
	struct Platform {
	public:
		Platform();
		~Platform();
		void create_window(const char* title, int width, int height);
		void handle_resize(int width, int height);
		double get_time();
		void swap_buffers();
		void capture_mouse(bool capture);
		bool capture = true;
	private:
		SDL_Window *mWindowHandle;
		SDL_GLContext mContext;
		double mFreq;
		Uint64 mStart;
	};
}
