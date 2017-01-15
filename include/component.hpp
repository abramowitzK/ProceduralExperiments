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
		static void expose_to_script();
		ComponentType mType;
		GameObject* mOwner;
	};
}

#endif // !
