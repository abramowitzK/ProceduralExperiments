#include "rigid_body.hpp"
#include <game_object.hpp>

namespace Aurora {
RigidBody::RigidBody(bool isStatic) : mIsStatic(isStatic) {
    mType = ComponentType::Physics;
}

void RigidBody::update(double dt) {
    if (!mIsStatic) {
    }
}
} // namespace Aurora
