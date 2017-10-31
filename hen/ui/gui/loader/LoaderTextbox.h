
#pragma once

#include "hen/ui/gui/Widget.h"

#include "extern/pugixml/pugixml.hpp"

namespace hen
{
	namespace gui
	{
		class LoaderTextbox
		{
		public:
			LoaderTextbox() = delete;
			LoaderTextbox(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node);

		private:
			void restoreSize(const glm::vec2& size);
			void limitTextSize();

			Widget& m_widget;
		};
	}
}