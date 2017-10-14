
#pragma once

#include "hen/ui/gui/Widget.h"

#include "extern/pugixml/pugixml.hpp"

namespace hen
{
	namespace gui
	{
		class LoaderButton
		{
		public:
			LoaderButton() = delete;
			LoaderButton(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node);

		private:
			void loadClickable(const pugi::xml_node& node);

			Widget& m_widget;
		};

		class LoaderButtonCheckbox
		{
		public:
			LoaderButtonCheckbox() = delete;
			LoaderButtonCheckbox(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node);

		private:
			Widget& m_widget;
		};

		class LoaderButtonRadio
		{
		public:
			LoaderButtonRadio() = delete;
			LoaderButtonRadio(Widget& widget) : m_widget(widget) {}

			void load(const pugi::xml_node& node);

		private:
			Widget& m_widget;
		};
	}
}