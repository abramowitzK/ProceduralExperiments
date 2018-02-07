#pragma once
#include <SDL.h>
#include <functional>
#include <key_state.hpp>
#include <mouse_state.hpp>
#include <vector>

namespace Aurora {
enum Keys {
    a = SDL_SCANCODE_A,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    space = SDL_SCANCODE_SPACE,
};
template <typename E> constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}
enum class Intents : uint8_t {
    Shutdown,
    Resize,
    Escape,
    Debug,
};
struct EventManager {
    static void init();
    static void poll_input();
    static void
    subscribe_to_resize_event(const std::function<void(int, int)>&& behaviour) {
        mSubscribers[to_underlying(Intents::Resize)].push_back(
            std::bind(behaviour, std::ref(mResizeX), std::ref(mResizeY)));
    }
    static void subscribe_to_event(Intents                       intent,
                                   const std::function<void()>&& f) {
        mSubscribers[to_underlying(intent)].push_back(f);
    }
    static bool  get_key_down(Keys key);
    static float get_mouse_relative_x();
    static float get_mouse_relative_y();
    static void  update_previous();
    static int   mResizeX;
    static int   mResizeY;
    static bool  debug;

  private:
    static void notify_subscribers();

  private:
    static std::vector<std::vector<std::function<void()>>> mSubscribers;
    static std::vector<bool>                               mIntents;
    static SDL_Event                                       mEvent;
    static int                                             mMouseRelX;
    static int                                             mMouseRelY;
    static KeyState                                        sKeyboardState;
    static MouseState                                      sMouseState;
    static bool                                            mDirty;
};
} // namespace Aurora
