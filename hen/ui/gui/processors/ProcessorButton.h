
#pragma once

#include "hen/event/events/Mouse.h"
#include "hen/ui/gui/Widget.h"

#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class ProcessorButton
		{
		public:
			ProcessorButton() = delete;
			ProcessorButton(Widget& widget) : m_widget(widget) {}

			void operator()();
			void operator()(const glm::vec2& offset, float dt) const;

			void operator()(events::MouseMove& event);
			void operator()(events::MousePress& event);
			void operator()(events::MouseRelease& event);
			
		private:
			std::string getIconState() const;
			std::string getIconClickState() const;
			std::string getIconActiveState() const;

			Widget& m_widget;
		};

		class ProcessorButtonCheckbox
		{
		public:
			ProcessorButtonCheckbox() = delete;
			ProcessorButtonCheckbox(Widget& widget) : m_widget(widget) {}

			void operator()();

		private:
			Widget& m_widget;
		};

		class ProcessorButtonRadio
		{
		public:
			ProcessorButtonRadio() = delete;
			ProcessorButtonRadio(Widget& widget) : m_widget(widget) {}

			void operator()();

		private:
			Widget& m_widget;
		};
	}
}