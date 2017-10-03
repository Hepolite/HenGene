
#pragma once

#include <glm/glm.hpp>

namespace hen
{
	namespace gui
	{
		class Widget;

		class ComponentSize
		{
		public:
			inline void setSize(const glm::vec2& size) { m_size = size; }
			inline void setMaxSize(const glm::vec2& max) { m_maxSize = max; }
			void setMinSize(const glm::vec2& min);

			inline glm::vec2 getSize() const { return m_size; }
			inline glm::vec2 getMaxSize() const { return m_maxSize; }
			inline glm::vec2 getMinSize() const { return m_minSize; }
			glm::vec2 getMinSize(const Widget& widget, bool ignoreLimits = false) const;

		private:
			glm::vec2 m_size;
			glm::vec2 m_minSize;
			glm::vec2 m_maxSize{ 1000000.0 };
		};
	}
}