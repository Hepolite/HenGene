
#pragma once

#include "hen/io/File.h"
#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>
#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class LoaderPanel
		{
		public:
			LoaderPanel() = delete;
			LoaderPanel(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node) const;

		private:
			Widget& m_widget;
		};
	}
}