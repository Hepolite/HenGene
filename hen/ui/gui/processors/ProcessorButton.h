
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
			void operator()(float dt);
			void operator()(const glm::vec2& offset, float dt) const;

		private:
			void handleMouseMove();
			void handleMousePress();
			void handleMouseRelease();

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