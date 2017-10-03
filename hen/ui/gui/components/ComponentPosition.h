
#pragma once

#include <glm/glm.hpp>

namespace hen
{
	namespace gui
	{
		class ComponentPosition
		{
		public:
			inline void setPos(const glm::vec2& pos) { m_pos = pos; }
			inline void setOffset(const glm::vec2& offset) { m_offset = offset; }

			inline glm::vec2 getPos() const { return m_pos; }
			inline glm::vec2 getOffset() const { return m_offset; }

		private:
			glm::vec2 m_pos;
			glm::vec2 m_offset;
		};
	}
}