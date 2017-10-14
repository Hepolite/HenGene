
#pragma once

#include "hen/ui/gui/Widget.h"

#include "extern/pugixml/pugixml.hpp"

namespace hen
{
	namespace gui
	{
		class LoaderBase
		{
		public:
			LoaderBase() = delete;
			LoaderBase(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node);

		private:
			void loadHeader(const pugi::xml_node& node);
			void loadFamily(const pugi::xml_node& node);

			void loadBorder(const pugi::xml_node& node);
			void loadClickable(const pugi::xml_node& node);
			void loadGroup(const pugi::xml_node& node);
			void loadLink(const pugi::xml_node& node);
			void loadPosition(const pugi::xml_node& node);
			void loadScript(const pugi::xml_node& node);
			void loadSize(const pugi::xml_node& node);
			void loadSprite(const pugi::xml_node& node);

			void assignDefaultGroup();
			void assignDefaultLink();

			Widget& m_widget;
		};
	}
}