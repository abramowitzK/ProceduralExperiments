//
// Created by Kyle on 12/8/2016.
//

#include "platform.hpp"
#include "events.hpp"
#include "rendering.hpp"


#undef main
using namespace CBlocks;

int main(int argc, char** argv){
	Platform platform;
	EventManager input;
	int width = 1280;
	int height = 768;
	platform.create_window("Hello SDL", width, height);
	Renderer renderer(width, height);
	renderer.create_camera(input);
	bool running = true;
	std::function<void()> shutdown = [&running](){ running = false;};
	input.subscribe_to_argless_event(Intents::Shutdown, shutdown);
	input.subscribe_to_resize_event([&platform](int a, int b){platform.handle_resize(a,b);});
	input.subscribe_to_resize_event([&renderer](int a, int b){renderer.handle_resize(a,b);});
	//input.subscribe_to_mouse_motion_event([](int x, int y){printf("%d %d\n", x, y);});
	double current_time = platform.get_time();
	double accumulator = 0;
	double t = 0;
	double dt = 0.01;
	while (running) {
		double new_time = platform.get_time();
		double frame_time = new_time - current_time;
		if (frame_time > 0.25)
			frame_time = 0.25;
		current_time = new_time;
		accumulator += frame_time;
		input.poll_input();
		while (accumulator >= dt) {
			t += dt;
			accumulator -= dt;
		}
		renderer.update(frame_time);
		renderer.clear_screen(true, true);
		renderer.render();
		platform.swap_buffers();
		input.update_previous();
	}
}

