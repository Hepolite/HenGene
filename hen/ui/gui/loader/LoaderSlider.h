
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
			void load(Widget& widget, const pugi::xml_node& node) const;

			static void setLimit(Widget& widget, const glm::vec2& limit, float middle);
			static void setValue(Widget& widget, float value);
			static float getValue(const Widget& widget);

		private:
			void loadData(Widget& widget, const pugi::xml_node& node) const;
			void loadButtons(Widget& widget, const pugi::xml_node& node) const;
			void loadButtonChange(Widget& widget, Widget& button, const pugi::xml_node& node, bool increase) const;
			void loadButtonBar(const Widget& widget, Widget& button, const pugi::xml_node& node) const;
			void loadCallback(Widget& widget) const;

			static void process(Widget& widget, float dt);
			static void render(const Widget& widget, const glm::vec2& offset, float dt);
			static void renderBar(const Widget& widget, const glm::vec2& offset);
			static void renderSlider(const Widget& widget, const glm::vec2& offset);
		};
	}
}