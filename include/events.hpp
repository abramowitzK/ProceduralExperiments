/*
* Created by Kyle on 12/10/2016.
* Copyright (c) 2016 Kyle All rights reserved.
*/

#ifndef CBLOCKS_INPUT_HPP
#define CBLOCKS_INPUT_HPP
#include <functional>
#include <vector>
#include <SDL.h>
namespace CBlocks {
	template<typename E>
	constexpr auto to_underlying(E e) noexcept {
		return static_cast<std::underlying_type_t<E>>(e);
	}
	enum class Intents : uint8_t {
		MoveForward,
		StrafeLeft,
		StrafeRight,
		MoveBackward,
		Jump,
		Look,
		Shutdown,
		Resize,
	};
	struct EventManager {
		EventManager();
		void poll_input();
		void subscribe_to_argless_event(Intents intent, std::function<void()> behaviour){
			mSubscribers[to_underlying(intent)].push_back(behaviour);
		}
		void subscribe_to_movement_events(std::function<void(Intents,double)> behaviour){
			mSubscribers[to_underlying(Intents::MoveForward)].push_back(std::bind(behaviour, Intents::MoveForward, std::ref(delta_time)));
			mSubscribers[to_underlying(Intents::StrafeLeft)].push_back(std::bind(behaviour, Intents::StrafeLeft,std::ref(delta_time)));
			mSubscribers[to_underlying(Intents::StrafeRight)].push_back(std::bind(behaviour, Intents::StrafeRight,std::ref(delta_time)));
			mSubscribers[to_underlying(Intents::MoveBackward)].push_back(std::bind(behaviour, Intents::MoveBackward,std::ref(delta_time)));
			mSubscribers[to_underlying(Intents::Jump)].push_back(std::bind(behaviour, Intents::Jump, std::ref(delta_time)));
		}
		void subscribe_to_resize_event(std::function<void(int,int)> behaviour){
			mSubscribers[to_underlying(Intents::Resize)].push_back(std::bind(behaviour, std::ref(mResizeX), std::ref(mResizeY)));
		}
		void subscribe_to_mouse_motion_event( std::function<void(int,int)> behaviour){
			mSubscribers[to_underlying(Intents::Look)].push_back(std::bind(behaviour, std::ref(mMouseRelX), std::ref(mMouseRelY)));
		}
		float delta_time;
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
		float mDt;

	};
}
#endif //CBLOCKS_INPUT_HPP
