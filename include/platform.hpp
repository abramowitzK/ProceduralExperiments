/*
* Created by Kyle on 12/10/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/

#ifndef CBLOCKS_PLATFORM_HPP
#define CBLOCKS_PLATFORM_HPP

#include <SDL2\SDL.h>
#include <SDL2\SDL_filesystem.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <type_traits>
namespace CBlocks {
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
		void handle_resize(int width, int height){
			printf("Resizing to %d, %d\n", width, height);
		}
		double get_time();
		void swap_buffers();
	private:
		SDL_Window *mWindowHandle;
		double mFreq;
		Uint64 mStart;
	};
	Platform::Platform(){
		SDL_Init(SDL_INIT_EVERYTHING);
		mFreq = static_cast<double>(SDL_GetPerformanceFrequency());
		mStart = SDL_GetPerformanceCounter();
	}
	Platform::~Platform(){
		SDL_DestroyWindow(mWindowHandle);
		SDL_Quit();
	}
	void Platform::create_window(const char *title, int width, int height){
		SDL_SetRelativeMouseMode(SDL_TRUE);
		mWindowHandle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		//SDL_SetWindowFullscreen(mWindowHandle, SDL_WINDOW_FULLSCREEN_DESKTOP);
	//	SDL_SetWindowSize(mWindowHandle,1920,1080);
	}

	double Platform::get_time(){
		return static_cast<double>(SDL_GetPerformanceCounter() - mStart) / mFreq;
	}
	void Platform::swap_buffers(){
	}
}

#endif //CBLOCKS_PLATFORM_HPP
