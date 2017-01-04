#pragma once
/**==============================================================================
*Purose: To encapsulate the state of the keyboard (both current and previous)<br>
*Usage: The Input class utilizes this abstraction
*/
namespace CBlocks {
	class KeyState final {
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
		Sets a key down in m_current(sets to 1)
		@param code Represents the code from the standard USB keyboard codes. This should always use Input::Keys
		*/
		void KeyDown(const int code);
		/**
		Sets a key up in m_current (sets to 0)
		@param code Represents the code from the standard USB keyboard codes. This should always use Input::Keys
		*/
		void KeyUp(const int code);
		/**
		Checks if key is currently down
		@param code Represents the code from the standard USB keyboard codes. This should always use Input::Keys
		@return Returns true if key is down and false otherwise
		*/
		bool IsKeyPressed(const int code) const;
		/**
		Copies the current values into the previous values. This will be updated once per frame. The previous structure will
		always represent the KeyState of the frame before the current one
		*/
		void UpdatePrev();
	private:
		size_t SIZE = 256;
		bool* m_current;
		bool* m_previous;
		bool* m_arrayMem;
	};
}