#include <mouse_state.hpp>
namespace CBlocks {
	MouseState::MouseState() : m_x(0), m_y(0), m_xRel(0), m_yRel(0) {
		memset(m_mouseButtonState, 0, NUM_MOUSE_BUTTONS);
	}

	MouseState::~MouseState() {
		delete[] m_prevXRel;
		delete[] m_prevYRel;
	}

	void MouseState::SetPosition(const int x, const int y) {
		m_x = x;
		m_y = y;
	}

	int MouseState::GetMouseX() const {
		return m_xRel;
	}

	int MouseState::GetMouseY() const {
		return m_yRel;
	}

	void MouseState::UpdatePrev() {
		m_prevX = m_x;
		m_prevY = m_y;
		m_xRel = 0;
		m_yRel = 0;
		memcpy(m_prevMouseButtonState, m_mouseButtonState, NUM_MOUSE_BUTTONS * sizeof(char));
	}
}
