
#pragma once

#include "hen/render/Text.h"
#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>
#include <glm/vec2.hpp>

#include <string>

namespace hen
{
	namespace gui
	{
		class LoaderTextfield
		{
		public:
			void load(Widget& widget, const pugi::xml_node& node) const;

			static render::Text getText(const Widget& widget);
			static void setText(Widget& widget, const render::Text& text);

			static std::string getValue(const Widget& widget);
			static void setValue(Widget& widget, const std::string& text);

		private:
			void loadText(Widget& widget, const pugi::xml_node& node) const;
			void loadButton(Widget& widget, const pugi::xml_node& node) const;

			static void process(Widget& widget, float dt);
			static void render(const Widget& widget, const glm::vec2& offset, float dt);
		};
	}
}