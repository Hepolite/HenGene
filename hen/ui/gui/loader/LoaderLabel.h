
#pragma once

#include "hen/render/Text.h"
#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>
#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class LoaderLabel
		{
		public:
			LoaderLabel() = delete;
			LoaderLabel(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node) const;

		private:
			void loadText(const pugi::xml_node& node) const;

			Widget& m_widget;
		};
	}
}