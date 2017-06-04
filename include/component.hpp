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
	};
	struct Component {
		static void expose_to_script(ScriptManager* m);
		ComponentType mType;
		GameObject* mOwner;
		Transform* mTransform = nullptr;
		std::string mTag;
	};
}

