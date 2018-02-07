#pragma once
#include <game_object.hpp>
#include <rendering.hpp>
#include <resource_manager.hpp>
#include <string>
struct ResourceManager;
namespace Aurora {
struct Scene {
    Scene();
    ~Scene();
    void                     init() { root.init(); }
    void                     render(Renderer* renderer);
    void                     update(double dt);
    GameObject*              create_object();
    GameObject               root;
    uint64_t                 mID;
    std::vector<GameObject*> mObjects;
    ResourceManager          mManager;
    Renderer*                mRenderer;
    std::string              mName;
};
} // namespace Aurora
