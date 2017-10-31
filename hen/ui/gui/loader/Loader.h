
#pragma once

#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>

namespace hen
{
	namespace gui
	{
		class Loader
		{
		public:
			Loader() = delete;
			Loader(GuiBase& gui);
			Loader(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node, const std::string& type);

		private:
			Widget& m_widget;
		};
	}
}