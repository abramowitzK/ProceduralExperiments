/*
* Created by Kyle on 12/10/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/

#ifndef CBLOCKS_INPUT_HPP
#define CBLOCKS_INPUT_HPP
#include <functional>
#include <vector>
#include <SDL2\SDL.h>
#include <key_state.hpp>
#include <mouse_state.hpp>
namespace CBlocks {
	enum Keys {
		a = SDL_SCANCODE_A,
		b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z

	};
	template<typename E>
	constexpr auto to_underlying(E e) noexcept {
		return static_cast<std::underlying_type_t<E>>(e);
	}
	enum class Intents : uint8_t {
		Shutdown,
		Resize,
	};
	struct EventManager {
		EventManager();
		void poll_input();
		void subscribe_to_argless_event(Intents intent, std::function<void()> behaviour){
			mSubscribers[to_underlying(intent)].push_back(behaviour);
		}
		void subscribe_to_resize_event(std::function<void(int,int)> behaviour){
			mSubscribers[to_underlying(Intents::Resize)].push_back(std::bind(behaviour, std::ref(mResizeX), std::ref(mResizeY)));
		}
		static bool get_key_down(Keys key);
		static float get_mouse_relative_x();
		static float get_mouse_relative_y();
		void update_previous();
	private:
		void notify_subscribers();
	private:
		std::vector<std::vector<std::function<void()>>> mSubscribers;
		std::vector<bool> mIntents;
		SDL_Event mEvent;
		int mResizeX;
		int mResizeY;
		int mMouseRelX;
		int mMouseRelY;
		static KeyState sKeyboardState;
		static MouseState sMouseState;

	};
}
#endif //CBLOCKS_INPUT_HPP
