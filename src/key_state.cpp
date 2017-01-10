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
		mArrayMem = (bool*)malloc(sizeof(bool)*SIZE * 2);
		if (NULL == mArrayMem) {
			//Crash and burn. This is not good. Malloc failed for some reason
			assert(false);
		}
		//Dangerous!! But I think we got this right...Should test to make sure
		mCurrent = mArrayMem;
		mPrevious = mArrayMem + SIZE;
		//Not sure if necessary but we'll include it anyway for safety as this should never be 
		//called in a tight loop and we're not worried about wasting clock cycles. 
		memset(mArrayMem, 0, SIZE * 2 * sizeof(bool));
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