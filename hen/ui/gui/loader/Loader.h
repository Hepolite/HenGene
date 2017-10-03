
#pragma once

#include "hen/io/File.h"
#include "hen/ui/gui/Gui.h"
#include "hen/ui/gui/Widget.h"

#include <extern/pugixml/pugixml.hpp>

#include <string>
#include <vector>

namespace hen
{
	namespace gui
	{
		class Loader
		{
		public:
			void load(Gui& gui, const io::File& file) const;

		private:
			void load(Widget& widget, const pugi::xml_node& node) const;
			void loadAsset(Widget& widget, const pugi::xml_node& node) const;
			void loadBorder(Widget& widget, const pugi::xml_node& node) const;
			void loadClickable(Widget& widget, const pugi::xml_node& node) const;
			void loadFamily(Widget& widget, const pugi::xml_node& node) const;
			void loadGroup(Widget& widget, const pugi::xml_node& node) const;
			void loadLink(Widget& widget, const pugi::xml_node& node) const;
			void loadPosition(Widget& widget, const pugi::xml_node& node) const;
			void loadScript(Widget& widget, const pugi::xml_node& node) const;
			void loadSize(Widget& widget, const pugi::xml_node& node) const;

			mutable std::string m_path;
			mutable std::vector<Widget*> m_actives;
		};
	}
}