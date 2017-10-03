
#pragma once

#include "hen/event/events/Mouse.h"
#include "hen/event/Listener.h"

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include <unordered_set>

namespace hen
{
	namespace ui
	{
		class Mouse
		{
		public:
			Mouse() = default;
			Mouse(const Mouse&) = delete;
			Mouse(Mouse&&) = delete;
			~Mouse() = default;

			Mouse& operator=(const Mouse&) = delete;
			Mouse& operator=(Mouse&&) = delete;

			void initialize();
			void deinitialize();
			void process();

			inline bool isHeld(unsigned int button) const { return m_held.find(button) != m_held.end(); }
			inline bool isPressed(unsigned int button) const { return m_pressed.find(button) != m_pressed.end(); }
			inline bool isReleased(unsigned int button) const { return m_released.find(button) != m_released.end(); }

			inline glm::vec2 getPos() const { return glm::vec2{ m_pos }; }
			inline glm::vec2 getDeltaPos() const { return glm::vec2{ m_delta }; }
			inline float getScroll() const { return m_pos.z; }
			inline float getDeltaScroll() const { return m_delta.z; }

			void setPos(const glm::ivec2& pos) const;

		private:
			event::Listener m_move;
			event::Listener m_press;
			event::Listener m_release;

			glm::vec4 m_pos, m_delta;

			std::unordered_set<unsigned int> m_held;
			std::unordered_set<unsigned int> m_pressed;
			std::unordered_set<unsigned int> m_released;
		};
	}
}