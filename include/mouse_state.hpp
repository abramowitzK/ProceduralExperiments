#pragma once
#include <memory>
/*****************************************************************************************
 * Represents the state of the mouse at a given point in time. Keeps track of
 *button state as well as positional info.
 ******************************************************************************************
 * Kyle.Abramowitz 07/2016
 */
namespace Aurora {
class MouseState {
  public:
    MouseState();
    ~MouseState();
    void set_position(const int x, const int y);
    int  get_mouse_x() const;
    int  get_mouse_y() const;
    void update_prev();
    void set_relative(int x, int y);

  private:
    const static size_t NUM_MOUSE_BUTTONS = 4;
    char                mMouseButtonState[NUM_MOUSE_BUTTONS];
    int                 mX;
    int                 mY;
    int                 mXRel;
    int                 mYRel;
    char                mPrevMouseButtonState[NUM_MOUSE_BUTTONS];
    int                 mPrevX;
    int                 mPrevY;
    int*                mPrevXRel;
    int*                mPrevYRel;
};
} // namespace Aurora
