
#pragma once

#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>

namespace hen
{
	namespace gui
	{
		class LoaderTextfield
		{
		public:
			LoaderTextfield() = delete;
			LoaderTextfield(Widget& widget) : m_widget(widget) {}
			
			void load(const pugi::xml_node& node);

		private:
			Widget& m_widget;
		};
	}
}