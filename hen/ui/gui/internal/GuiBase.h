
#pragma once

#include "hen/ui/gui/internal/GuiLayer.h"
#include "hen/ui/gui/internal/GuiResources.h"

namespace hen
{
	namespace gui
	{
		class GuiBase
		{
		public:
			GuiBase() = delete;
			GuiBase(GuiLayer layer) : m_layer(layer) {}
			GuiBase(const GuiBase&) = delete;
			GuiBase(GuiBase&&) = delete;
			~GuiBase() = default;

			GuiBase& operator=(const GuiBase&) = delete;
			GuiBase& operator=(GuiBase&&) = delete;

			void process(float dt);
			void render(float dt) const;

			inline GuiLayer getLayer() const { return m_layer; }
			inline GuiResources& getResources() { return m_resources; }

			inline bool hasWidget(const std::string& name = "") const { return m_resources.hasWidget(name); }
			inline Widget& getWidget(const std::string& name = "") { return m_resources.getWidget(name); }

		private:
			GuiLayer m_layer = GuiLayer::NORMAL_PRIORITY;
			GuiResources m_resources;
		};
	}
}