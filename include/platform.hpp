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
		SDL_GLContext mContext;
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
		SDL_GL_DeleteContext(mContext);
		SDL_Quit();
	}
	void Platform::create_window(const char *title, int width, int height){
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		mWindowHandle = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		mContext = SDL_GL_CreateContext(mWindowHandle);
		SDL_SetWindowFullscreen(mWindowHandle, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_SetWindowSize(mWindowHandle,1920,1080);
	}

	double Platform::get_time(){
		return static_cast<double>(SDL_GetPerformanceCounter() - mStart) / mFreq;
	}
	void Platform::swap_buffers(){
		SDL_GL_SwapWindow(mWindowHandle);
	}
}

#endif //CBLOCKS_PLATFORM_HPP
