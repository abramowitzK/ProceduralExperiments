#ifndef CBLOCKS_SCRIPT_MANAGER_HPP
#define CBLOCKS_SCRIPT_MANAGER_HPP
#include <vector>
namespace CBlocks {

	struct ScriptManager {
		void update(double dt);
		void init();
		static ScriptManager* instance() {
			if (!s_instance) {
				s_instance = new ScriptManager();
			}
			return s_instance;
		}
	private:
		static ScriptManager* s_instance;
	};
}
#endif