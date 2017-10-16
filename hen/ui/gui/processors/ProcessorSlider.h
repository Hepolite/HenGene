
#pragma once

#include "hen/ui/gui/Widget.h"

#include <glm/vec2.hpp>

namespace hen
{
	namespace gui
	{
		class ProcessorSlider
		{
		public:
			ProcessorSlider() = delete;
			ProcessorSlider(Widget& widget) : m_widget(widget) {}

			void operator()();
			void operator()(float dt);
			void operator()(const glm::vec2& offset, float dt) const;

			float getSnap() const;
			float getValue() const;
			void setValue(float value);
			void increment();
			void decrement();

		private:
			void processChildren(float dt);
			void processSlider(float dt);

			void renderChildren(const glm::vec2& offset, float dt) const;
			void renderBar(const glm::vec2& offset, float dt) const;
			void renderSlider(const glm::vec2& offset, float dt) const;

			std::string getIconClickState(Widget& widget) const;

			Widget& m_widget;
		};
	}
}