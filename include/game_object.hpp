#pragma once
#include <transform.hpp>
#include <vector>
namespace Aurora {
enum class ComponentType;
struct Renderer;
struct Component;
struct GameObject {
    friend struct Scene;
    ~GameObject();
    std::vector<GameObject*> mChildren;
    void                     update(double dt);
    void                     render(Renderer* renderer);
    void                     add_component(Component* comp);
    Component*               get_component_base(ComponentType type);
    template <typename T> T* get_component(ComponentType type) { return static_cast<T*>(get_component_base(type)); }
    void                     init();
    GameObject*              parent;
    Transform                transform;

  private:
    uint64_t mId;
    GameObject();
    GameObject(GameObject* parent);
    std::vector<Component*> mComponents;
};

} // namespace Aurora
