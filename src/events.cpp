/*
* Created by Kyle on 12/11/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/
#include "events.hpp"
namespace CBlocks {
	EventManager::EventManager() {
		mIntents.resize(UINT8_MAX);
		mSubscribers.resize(UINT8_MAX);
	};

	void EventManager::poll_input() {
		while(SDL_PollEvent(&mEvent)) {
			switch(mEvent.type) {
				case SDL_KEYDOWN:
					if(mEvent.key.keysym.scancode == SDL_SCANCODE_W) {
						mIntents[to_underlying(Intents::MoveForward)] = true;
					}
					if(mEvent.key.keysym.scancode == SDL_SCANCODE_A) {
						mIntents[to_underlying(Intents::StrafeLeft)] = true;
					}
					if(mEvent.key.keysym.scancode == SDL_SCANCODE_S) {
						mIntents[to_underlying(Intents::MoveBackward)] = true;
					}
					if(mEvent.key.keysym.scancode == SDL_SCANCODE_D) {
						mIntents[to_underlying(Intents::StrafeRight)] = true;
					}
					break;
				case SDL_KEYUP:
					if(mEvent.key.keysym.scancode == SDL_SCANCODE_W) {
						mIntents[to_underlying(Intents::MoveForward)] = false;
					}
					if(mEvent.key.keysym.scancode == SDL_SCANCODE_A) {
						mIntents[to_underlying(Intents::StrafeLeft)] = false;
					}
					if(mEvent.key.keysym.scancode == SDL_SCANCODE_S) {
						mIntents[to_underlying(Intents::MoveBackward)] = false;
					}
					if(mEvent.key.keysym.scancode == SDL_SCANCODE_D) {
						mIntents[to_underlying(Intents::StrafeRight)] = false;
					}
					break;
				case SDL_QUIT:
					mIntents[to_underlying(Intents::Shutdown)] = true;
					break;
				case SDL_MOUSEMOTION:
					mIntents[to_underlying(Intents::Look)] = true;
					mMouseRelX = mEvent.motion.xrel;
					mMouseRelY = mEvent.motion.yrel;
					break;
				case SDL_WINDOWEVENT:
					switch(mEvent.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							mIntents[to_underlying(Intents::Resize)] = true;
							mResizeX = mEvent.window.data1;
							mResizeY = mEvent.window.data2;
							break;
						default:
							break;
					}
				default:
					break;
			}
		}
		//End of input processing for this frame. Notify all subscribers and run their functions
		notify_subscribers();
	}

	void EventManager::notify_subscribers() {
		for(unsigned i = 0; i < mIntents.size(); i++) {
			if(mIntents[i]) {
				for(const auto &func: mSubscribers[i]) {
					func();
				}
			}
		}
		std::fill(mIntents.begin()+5, mIntents.end(), 0);
	}
}
