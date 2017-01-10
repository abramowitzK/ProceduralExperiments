#pragma once
/**==============================================================================
*Purose: To encapsulate the state of the keyboard (both current and previous)<br>
*Usage: The Input class utilizes this abstraction
*/
namespace CBlocks {
	class KeyState {
	public:
		/**
		Construct a keystate object and initialize its internal data structures
		*/
		KeyState();
		/**
		Cleans up memory and nulls the pointers
		*/
		~KeyState();
		/**
		Sets a key down in mCurrent(sets to 1)
		@param code Represents the code from the standard USB keyboard codes. This should always use Input::Keys
		*/
		void key_down(const int code);
		/**
		Sets a key up in mCurrent (sets to 0)
		@param code Represents the code from the standard USB keyboard codes. This should always use Input::Keys
		*/
		void key_up(const int code);
		/**
		Checks if key is currently down
		@param code Represents the code from the standard USB keyboard codes. This should always use Input::Keys
		@return Returns true if key is down and false otherwise
		*/
		bool is_key_pressed(const int code) const;
		/**
		Copies the current values into the previous values. This will be updated once per frame. The previous structure will
		always represent the KeyState of the frame before the current one
		*/
		void update_prev();
	private:
		size_t SIZE = 256;
		bool* mCurrent;
		bool* mPrevious;
		bool* mArrayMem;
	};
}