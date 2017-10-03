
#pragma once

#include <glm/glm.hpp>

namespace hen
{
	namespace gui
	{
		class Widget;

		class ComponentLink
		{
		public:
			enum class Location
			{
				TOP_LEFT, TOP, TOP_RIGHT,
				LEFT_TOP, RIGHT_TOP,
				LEFT, CENTER, RIGHT,
				LEFT_BOTTOM, RIGHT_BOTTOM,
				BOTTOM_LEFT, BOTTOM, BOTTOM_RIGHT
			};

			inline void setTarget(const Widget* target) { m_target = target; }
			inline void setLocation(Location location) { m_location = location; }

			inline const Widget* getTarget() const { return m_target; }
			inline Location getLocation() const { return m_location; }

			glm::vec2 getPos(const Widget& self) const;

		private:
			glm::vec2 getInner(const Widget& self) const;
			glm::vec2 getOuter(const Widget& self) const;

			const Widget* m_target = nullptr;
			Location m_location = Location::TOP_LEFT;
		};
	}
}