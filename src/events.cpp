/*
* Created by Kyle on 12/11/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/
#include "events.hpp"

namespace CBlocks {
	KeyState EventManager::sKeyboardState;
	MouseState EventManager::sMouseState;
	EventManager::EventManager() {
		mIntents.resize(UINT8_MAX);
		mSubscribers.resize(UINT8_MAX);
	};

	void EventManager::poll_input() {
		while(SDL_PollEvent(&mEvent)) {
			switch(mEvent.type) {
				case SDL_KEYDOWN:
					if (mEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						mIntents[to_underlying(Intents::Escape)] = true;
						break;
					}
					sKeyboardState.KeyDown(mEvent.key.keysym.scancode);
					break;
				case SDL_KEYUP:
					sKeyboardState.KeyUp(mEvent.key.keysym.scancode);
					break;
				case SDL_QUIT:
					mIntents[to_underlying(Intents::Shutdown)] = true;
					break;
				case SDL_MOUSEMOTION:
					sMouseState.SetRelative(mEvent.motion.xrel, mEvent.motion.yrel);
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

	bool EventManager::get_key_down(Keys key) {
		return sKeyboardState.IsKeyPressed(key);
	}

	float EventManager::get_mouse_relative_x() {
		return (float)sMouseState.GetMouseX();
	}

	float EventManager::get_mouse_relative_y() {
		return (float)sMouseState.GetMouseY();
	}

	void EventManager::update_previous() {
		sMouseState.UpdatePrev();
		sKeyboardState.UpdatePrev();
	}

	void EventManager::notify_subscribers() {
		for(unsigned i = 0; i < mIntents.size(); i++) {
			if(mIntents[i]) {
				for(const auto &func: mSubscribers[i]) {
					func();
				}
				mIntents[i] = false;
			}
		}
	}
}
