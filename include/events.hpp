#pragma once
#include <functional>
#include <vector>
#include <SDL.h>
#include <key_state.hpp>
#include <mouse_state.hpp>

namespace Aurora {
	struct ScriptManager;
	enum Keys {
		a = SDL_SCANCODE_A, b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z, space = SDL_SCANCODE_SPACE, 
	};
	template<typename E>
	constexpr auto to_underlying(E e) noexcept {
		return static_cast<std::underlying_type_t<E>>(e);
	}
	enum class Intents : uint8_t {
		Shutdown,
		Resize,
		Escape,
		Debug,
	};
	struct EventManager {
		EventManager();
		void poll_input();
		void subscribe_to_resize_event(std::function<void(int,int)> behaviour){
			mSubscribers[to_underlying(Intents::Resize)].push_back(std::bind(behaviour, std::ref(mResizeX), std::ref(mResizeY)));
		}
		void subscribe_to_event(Intents intent, std::function<void()> f) {
			mSubscribers[to_underlying(intent)].push_back(f);
		}
		static bool get_key_down(Keys key);
		static float get_mouse_relative_x();
		static float get_mouse_relative_y();
		void update_previous();
		int mResizeX;
		int mResizeY;
		bool debug;
	private:
		void notify_subscribers();
	private:
		std::vector<std::vector<std::function<void()>>> mSubscribers;
		std::vector<bool> mIntents;
		SDL_Event mEvent;
		int mMouseRelX;
		int mMouseRelY;
		static KeyState sKeyboardState;
		static MouseState sMouseState;
		bool mDirty;
	};
}
