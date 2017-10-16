
#pragma once

#include "hen/io/File.h"
#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>
#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class LoaderSlider
		{
		public:
			LoaderSlider() = delete;
			LoaderSlider(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node);

		private:
			void loadData(const pugi::xml_node& node);

			void createChildren();
			void loadChildButton(Widget& child, bool incrementer) const;
			void loadChildBar(Widget& child) const;

			void limitSize();

			Widget& m_widget;
		};
	}
}