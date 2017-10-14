
#pragma once

#include <functional>

namespace hen
{
	namespace gui
	{
		class ComponentClickable
		{
		public:
			inline void invoke() const { if (m_invoker != nullptr) m_invoker(); }
			inline void setInvoker(const std::function<void()>& invoker) { m_invoker = invoker; }
			inline void setInvoker(std::function<void()>&& invoker) { m_invoker = invoker; }

			inline void setLocked(bool locked) { m_locked = locked; }
			inline void setHovered(bool hovered) { m_hovered = hovered; }
			inline void setClicked(bool clicked) { m_clicked = clicked; }

			inline bool isLocked() const { return m_locked; }
			inline bool isHovered() const { return m_hovered; }
			inline bool isClicked() const { return m_clicked; }

			inline void markForInvokationAfterLoad() { m_invokeAfterLoad = true; }
			inline bool shouldBeInvokedAfterLoad() const { return m_invokeAfterLoad; }

		private:
			std::function<void()> m_invoker;

			bool m_locked = false;
			bool m_hovered = false;
			bool m_clicked = false;
			bool m_invokeAfterLoad = false;
		};
	}
}