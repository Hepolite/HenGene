
#pragma once

#include <glm/glm.hpp>

namespace hen
{
	namespace gui
	{
		class ComponentBorder
		{
		public:
			inline void setOuter(const glm::vec4& border) { m_outer = border; }
			inline void setOuter(float left, float right, float top, float bottom) { setOuter(glm::vec4{ left, right, top, bottom }); }
			inline void setOuterLeft(float left) { m_outer.x = left; }
			inline void setOuterRight(float right) { m_outer.y = right; }
			inline void setOuterTop(float top) { m_outer.z = top; }
			inline void setOuterBottom(float bottom) { m_outer.w = bottom; }

			inline glm::vec4 getOuter() const { return m_outer; }
			inline float getOuterLeft() const { return m_outer.x; }
			inline float getOuterRight() const { return m_outer.y; }
			inline float getOuterTop() const { return m_outer.z; }
			inline float getOuterBottom() const { return m_outer.w; }


			inline void setInner(const glm::vec4& border) { m_inner = border; }
			inline void setInner(float left, float right, float top, float bottom) { setInner(glm::vec4{ left, right, top, bottom }); }
			inline void setInnerLeft(float left) { m_inner.x = left; }
			inline void setInnerRight(float right) { m_inner.y = right; }
			inline void setInnerTop(float top) { m_inner.z = top; }
			inline void setInnerBottom(float bottom) { m_inner.w = bottom; }

			inline glm::vec4 getInner() const { return m_inner; }
			inline float getInnerLeft() const { return m_inner.x; }
			inline float getInnerRight() const { return m_inner.y; }
			inline float getInnerTop() const { return m_inner.z; }
			inline float getInnerBottom() const { return m_inner.w; }

		private:
			glm::vec4 m_inner;
			glm::vec4 m_outer;
		};
	}
}