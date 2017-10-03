
#pragma once

#include "hen/io/File.h"
#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>
#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class LoaderWindow
		{
		public:
			void load(Widget& widget, const pugi::xml_node& node) const;

		private:
			void loadSliders(Widget& widget) const;
			void loadSlider(Widget& widget, Widget& slider, bool vertical) const;

			static void process(Widget& widget, float dt);
			static void render(const Widget& widget, const glm::vec2& offset, float dt);
		};
	}
}