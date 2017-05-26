/*
* Created by Kyle on 12/11/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/
#include "events.hpp"

namespace Aurora {
	KeyState EventManager::sKeyboardState;
	MouseState EventManager::sMouseState;
	EventManager::EventManager() {
		mIntents.resize(UINT8_MAX);
		mSubscribers.resize(UINT8_MAX);
		mDirty = false;
	};

	void EventManager::poll_input() {
		while(SDL_PollEvent(&mEvent)) {
			switch(mEvent.type) {
				case SDL_KEYDOWN:
					if (mEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
						mIntents[to_underlying(Intents::Escape)] = true;
						mDirty = true;
						break;
					}
					sKeyboardState.key_down(mEvent.key.keysym.scancode);
					break;
				case SDL_KEYUP:
					sKeyboardState.key_up(mEvent.key.keysym.scancode);
					break;
				case SDL_QUIT:
					mIntents[to_underlying(Intents::Shutdown)] = true;
					mDirty = true;
					break;
				case SDL_MOUSEMOTION:
					sMouseState.set_relative(mEvent.motion.xrel, mEvent.motion.yrel);
					break;
				case SDL_WINDOWEVENT:
					switch(mEvent.window.event) {
						case SDL_WINDOWEVENT_RESIZED:
							mIntents[to_underlying(Intents::Resize)] = true;
							mDirty = true;
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
		return sKeyboardState.is_key_pressed(key);
	}

	float EventManager::get_mouse_relative_x() {
		return (float)sMouseState.get_mouse_x();
	}

	float EventManager::get_mouse_relative_y() {
		return (float)sMouseState.get_mouse_y();
	}

	void EventManager::update_previous() {
		sMouseState.update_prev();
		sKeyboardState.update_prev();
	}

	void EventManager::notify_subscribers() {
		//Huge performance savings here. Only notify subscribers if we have to. Just need to remember 
		//to always set the dirty bit when we want an intent to be processed right away
		if (mDirty) {
			mDirty = false;
			for (unsigned i = 0; i < mIntents.size(); i++) {
				if (mIntents[i]) {
					for (const auto &func : mSubscribers[i]) {
						func();
					}
					mIntents[i] = false;
				}
			}
		}
	}
}
