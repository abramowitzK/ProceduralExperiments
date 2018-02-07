#pragma once
namespace Aurora {
	enum class ColliderTypes {
		Box,
		Sphere,
		Capsule,
		Mesh,
	};
	struct Physics {

		~Physics();
		void fixed_update(double dt);
		static Physics* instance() {
			if (!sInstance)
				sInstance = new Physics();
			return sInstance;
		}
		bool debug = true;
	private:
		Physics();
		static Physics* sInstance;
	};
}