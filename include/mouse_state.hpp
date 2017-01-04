#pragma once
#include <queue>
/*****************************************************************************************
* Represents the state of the mouse at a given point in time. Keeps track of button state
* as well as positional info.
******************************************************************************************
* Kyle.Abramowitz 07/2016
*/
namespace CBlocks {
	class MouseState {
	public:
		MouseState();
		~MouseState();
		void SetPosition(const int x, const int y);
		int GetMouseX() const;
		int GetMouseY() const;
		void UpdatePrev();
		inline void SetRelative(int x, int y);
	private:
		const static size_t NUM_MOUSE_BUTTONS = 4;
		char m_mouseButtonState[NUM_MOUSE_BUTTONS];
		int m_x;
		int m_y;
		int m_xRel;
		int m_yRel;
		char m_prevMouseButtonState[NUM_MOUSE_BUTTONS];
		int m_prevX;
		int m_prevY;
		int* m_prevXRel;
		int* m_prevYRel;
	};
	void MouseState::SetRelative(int x, int y) {
		m_xRel += x;
		m_yRel += y;
	}
}