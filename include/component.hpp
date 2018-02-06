#pragma once
#include <string>
namespace Aurora {
	struct ScriptManager;
	struct GameObject;
	class Transform;
	enum class ComponentType {
		Mesh,
		Script,
		Physics,
		Camera,
		CharacterController,
		GUIText,
		Sprite
	};
	struct Component {
		ComponentType mType;
		GameObject* mOwner;
		Transform* mTransform = nullptr;
		std::string mTag;
	};
}

