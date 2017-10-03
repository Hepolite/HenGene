
#pragma once

#include "hen/io/File.h"
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
			void load(Widget& widget, const pugi::xml_node& node) const;

			static void setText(Widget& widget, const render::Text& text);

		private:
			void loadText(Widget& widget, const pugi::xml_node& node) const;

			static void render(const Widget& widget, const glm::vec2& offset, float dt);
		};
	}
}