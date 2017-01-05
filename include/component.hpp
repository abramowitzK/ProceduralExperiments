#ifndef CBLOCKS_COMPONENT_HPP
#define CBLOCKS_COMPONENT_HPP
namespace CBlocks {
	enum class ComponentType {
		Mesh,
		Physics,
	};
	struct Component {
		ComponentType mType;
	};
}

#endif // !
