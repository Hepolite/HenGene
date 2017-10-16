
#pragma once

#include "hen/ui/gui/Widget.h"

#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class ProcessorLabel
		{
		public:
			ProcessorLabel() = delete;
			ProcessorLabel(Widget& widget) : m_widget(widget) {}

			void operator()(const glm::vec2& offset, float dt) const;

		private:
			Widget& m_widget;
		};
	}
}