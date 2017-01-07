#ifndef CBLOCKS_SCRIPT_HPP
#define CBLOCKS_SCRIPT_HPP
#include <functional>
struct Script {
	std::function<void(double)> OnUpdate;
};

#endif