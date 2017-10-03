
#pragma once

#include "hen/io/File.h"
#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>
#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class LoaderButton
		{
		public:
			void load(Widget& widget, const pugi::xml_node& node) const;

		private:
			void loadClickable(Widget& widget, const pugi::xml_node& node) const;
			void setupMouseEvent(Widget& widget) const;

			static void render(const Widget& widget, const glm::vec2& offset, float dt);
			static void renderIcon(const Widget& widget, const glm::vec2& offset);
		};

		class LoaderButtonCheckbox : public LoaderButton
		{
		public:
			void load(Widget& widget, const pugi::xml_node& node) const;

		private:
			void loadClickable(Widget& widget, const pugi::xml_node& node) const;
		};

		class LoaderButtonRadio : public LoaderButton
		{
		public:
			void load(Widget& widget, const pugi::xml_node& node) const;

		private:
			void loadClickable(Widget& widget, const pugi::xml_node& node) const;
		};
	}
}