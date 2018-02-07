#include <mouse_state.hpp>
namespace Aurora {
MouseState::MouseState() : mX(0), mY(0), mXRel(0), mYRel(0) { memset(mMouseButtonState, 0, NUM_MOUSE_BUTTONS); }

MouseState::~MouseState() {
    delete[] mPrevXRel;
    delete[] mPrevYRel;
}

void MouseState::set_position(const int x, const int y) {
    mX = x;
    mY = y;
}

int MouseState::get_mouse_x() const { return mXRel; }

int MouseState::get_mouse_y() const { return mYRel; }

void MouseState::update_prev() {
    mPrevX = mX;
    mPrevY = mY;
    mXRel  = 0;
    mYRel  = 0;
    memcpy(mPrevMouseButtonState, mMouseButtonState, NUM_MOUSE_BUTTONS * sizeof(char));
}
void MouseState::set_relative(int x, int y) {
    mXRel += x;
    mYRel += y;
}
} // namespace Aurora
