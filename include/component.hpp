#ifndef CBLOCKS_COMPONENT_HPP
#define CBLOCKS_COMPONENT_HPP

namespace CBlocks {
	struct GameObject;
	enum class ComponentType {
		Mesh,
		Script,
		Physics,
	};
	struct Component {
		ComponentType mType;
		GameObject* owner;
	};
}

#endif // !
