
#pragma once

#include "hen/ui/gui/Widget.h"

#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class ProcessorTextfield
		{
		public:
			ProcessorTextfield() = delete;
			ProcessorTextfield(Widget& widget) : m_widget(widget) {}

			void operator()(float dt) const;

		private:
			Widget& m_widget;
		};
	}
}