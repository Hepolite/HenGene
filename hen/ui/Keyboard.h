
#pragma once

#include "hen/event/Listener.h"

#include <allegro5/keycodes.h>

#include <unordered_set>

namespace hen
{
	namespace ui
	{
		class Keyboard
		{
		public:
			Keyboard() = default;
			Keyboard(const Keyboard&) = delete;
			Keyboard(Keyboard&&) = delete;
			~Keyboard() = default;

			Keyboard& operator=(const Keyboard&) = delete;
			Keyboard& operator=(Keyboard&&) = delete;

			void initialize();
			void deinitialize();
			void process();

			inline bool isHeld(unsigned int key) const { return m_held.find(key) != m_held.end(); }
			inline bool isPressed(unsigned int key) const { return m_pressed.find(key) != m_pressed.end(); }
			inline bool isReleased(unsigned int key) const { return m_released.find(key) != m_released.end(); }

		private:
			event::Listener m_press;
			event::Listener m_release;

			std::unordered_set<unsigned int> m_pressed;
			std::unordered_set<unsigned int> m_held;
			std::unordered_set<unsigned int> m_released;
		};
	}
}