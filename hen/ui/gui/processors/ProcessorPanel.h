
#pragma once

#include "hen/ui/gui/Widget.h"

namespace hen
{
	namespace gui
	{
		class ProcessorPanel
		{
		public:
			ProcessorPanel() = delete;
			ProcessorPanel(Widget& widget) : m_widget(widget) {}

			void operator()(const glm::vec2& offset, float dt) const;

		private:
			void renderBackground(const glm::vec2& offset, float dt) const;
			void renderChildren(const glm::vec2& offset, float dt) const;

			Widget& m_widget;
		};
	}
}