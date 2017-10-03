
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
			void load(Widget& widget, const pugi::xml_node& node) const;

		private:
			static void render(const Widget& widget, const glm::vec2& offset, float dt);
			static void renderBackground(const Widget& widget, const glm::vec2& offset);
		};
	}
}