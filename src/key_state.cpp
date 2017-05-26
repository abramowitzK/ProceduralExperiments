#include <key_state.hpp>
#include <cstring>
#include <cstdlib>
#include <cassert>
namespace Aurora {
	KeyState::KeyState() {
		//Allocate contiguous memory for two arrays of size SIZE.
		mArrayMem = (bool*)calloc(SIZE * 2, sizeof(bool));
		if (NULL == mArrayMem) {
			//Crash and burn. This is not good. alloc failed for some reason
			assert(false);
		}
		//Dangerous!! But I think we got this right...Should test to make sure
		mCurrent = mArrayMem;
		mPrevious = mArrayMem + SIZE;
	}

	KeyState::~KeyState() {
		if (mArrayMem)
			free(mArrayMem);
		//This shouldn't impact performance and safety is nice
		mCurrent = nullptr;
		mPrevious = nullptr;
		mArrayMem = nullptr;
	}

	void KeyState::key_down(int code) {
#ifdef _DEBUG
		assert(code < SIZE);
#endif
		if (code < SIZE) {
			mCurrent[code] = 1;
		}
	}

	void KeyState::key_up(int code) {
#ifdef _DEBUG
		assert(code < SIZE);
#endif
		if (code < SIZE) {
			mCurrent[code] = 0;
		}
	}

	bool KeyState::is_key_pressed(int code) const {
#ifdef _DEBUG
		assert(code < SIZE);
#endif
		if (code < SIZE) {
			return mCurrent[code];
		}
		return false;
	}

	void KeyState::update_prev() {
		memcpy(mPrevious, mCurrent, SIZE);
	}
}