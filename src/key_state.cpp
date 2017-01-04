#include <key_state.hpp>
#include <cstring>
#include <cstdlib>
#include <cassert>
namespace CBlocks {
	KeyState::KeyState() {
		//Allocate contiguous memory for two arrays of size SIZE. I want to avoid 
		//allocating this on the stack because it's going to be around for
		//the lifetime of the application and will take up a significant
		//amount of stack space. We'll do the allocation in one malloc call
		//because we're fancy. I'm using more of an idiomatic C style and 
		//am trying to avoid STL as much as possible
		m_arrayMem = (bool*)malloc(sizeof(bool)*SIZE * 2);
		if (NULL == m_arrayMem) {
			//Crash and burn. This is not good. Malloc failed for some reason
			assert(false);
		}
		//Dangerous!! But I think we got this right...Should test to make sure
		m_current = m_arrayMem;
		m_previous = m_arrayMem + SIZE;
		//Not sure if necessary but we'll include it anyway for safety as this should never be 
		//called in a tight loop and we're not worried about wasting clock cycles. 
		memset(m_arrayMem, 0, SIZE * 2 * sizeof(bool));
	}

	KeyState::~KeyState() {
		if (m_arrayMem)
			free(m_arrayMem);
		//This shouldn't impact performance and safety is nice
		m_current = nullptr;
		m_previous = nullptr;
		m_arrayMem = nullptr;
	}

	void KeyState::KeyDown(int code) {
#ifdef _DEBUG
		assert(code < SIZE);
#endif
		if (code < SIZE) {
			m_current[code] = 1;
		}
	}

	void KeyState::KeyUp(int code) {
#ifdef _DEBUG
		assert(code < SIZE);
#endif
		if (code < SIZE) {
			m_current[code] = 0;
		}
	}

	bool KeyState::IsKeyPressed(int code) const {
#ifdef _DEBUG
		assert(code < SIZE);
#endif
		if (code < SIZE) {
			return m_current[code];
		}
		return false;
	}

	void KeyState::UpdatePrev() {
		memcpy(m_previous, m_current, SIZE);
	}
}