
#pragma once

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 4

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace hen
{
	namespace events
	{
		class MouseEnterDisplay {};
		class MouseLeaveDisplay {};

		class MousePress
		{
		public:
			MousePress(unsigned int button, const glm::vec4 position)
				: m_button(button), m_pos(position)
			{}
			~MousePress() = default;

			inline unsigned int getButton() const { return m_button; }
			inline glm::vec4 getPos() const { return m_pos; }
			inline glm::vec2 getScreenPos() const { return glm::vec2{ m_pos }; }

		private:
			unsigned int m_button;
			glm::vec4 m_pos;
		};

		class MouseRelease
		{
		public:
			MouseRelease(unsigned int button, const glm::vec4 position)
				: m_button(button), m_pos(position)
			{}
			~MouseRelease() = default;

			inline unsigned int getButton() const { return m_button; }
			inline glm::vec4 getPos() const { return m_pos; }
			inline glm::vec2 getScreenPos() const { return glm::vec2{ m_pos }; }

		private:
			unsigned int m_button;
			glm::vec4 m_pos;
		};

		class MouseMove
		{
		public:
			MouseMove(const glm::vec4& delta, const glm::vec4& position)
				: m_delta(delta), m_pos(position)
			{}
			~MouseMove() = default;

			inline glm::vec4 getDelta() const { return m_delta; }
			inline glm::vec4 getPos() const { return m_pos; }
			inline glm::vec2 getScreenPos() const { return glm::vec2{ m_pos }; }

		private:
			glm::vec4 m_delta;
			glm::vec4 m_pos;
		};
	}
}