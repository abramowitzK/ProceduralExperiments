#pragma once
#include <component.hpp>
namespace Aurora {
class btKinematicCharacterController;

struct CharacterController : public Component{
	CharacterController(btKinematicCharacterController* controller);
	void update(double dt);
	btPairCachingGhostObject* mGhost;
	btKinematicCharacterController* mController;
};
}