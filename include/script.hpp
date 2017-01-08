#ifndef CBLOCKS_SCRIPT_HPP
#define CBLOCKS_SCRIPT_HPP
#include <sol.hpp>
#include <component.hpp>
namespace CBlocks {
	struct Script : public Component {
		Script(const std::string& tableName, std::string script);
		~Script() { printf("destructor called\n"); }
		void update(double dt);
		sol::table self;
		sol::function mUpdate;
		std::string mScript;
		void init();
	};
}

#endif