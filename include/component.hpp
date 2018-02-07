#pragma once
#include <string>
namespace Aurora {
struct GameObject;
class Transform;
enum class ComponentType {
    Mesh,
    Physics,
    Camera,
    CharacterController,
    GUIText,
    Sprite
};
struct Component {
    ComponentType mType;
    GameObject*   mOwner;
    Transform*    mTransform = nullptr;
    std::string   mTag;
};
} // namespace Aurora
