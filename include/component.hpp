#pragma once
namespace Aurora {
	struct ScriptManager;
	struct GameObject;
	enum class ComponentType {
		Mesh,
		Script,
		Physics,
	};
	struct Component {
		static void expose_to_script(ScriptManager* m);
		ComponentType mType;
		GameObject* mOwner;
	};
}

