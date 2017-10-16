
#pragma once

#include "hen/ui/gui/Gui.h"
#include "hen/ui/gui/GuiHandle.h"
#include "hen/ui/gui/GuiLayer.h"
#include "hen/render/Renderer.h"

#include <string>

namespace hen
{
	namespace gui
	{
		class GuiManager
		{
			using GuiList = std::vector<Gui*>;

		public:
			GuiManager();
			GuiManager(const GuiManager&) = delete;
			GuiManager(GuiManager&&) = delete;
			~GuiManager();

			void initialize();

			GuiManager& operator=(const GuiManager&) = delete;
			GuiManager& operator=(GuiManager&&) = delete;

			void process(float dt);
			void render(float dt) const;

			void add(Gui* gui, GuiLayer layer = GuiLayer::NORMAL_PRIORITY);
			void remove(Gui* gui, GuiLayer layer = GuiLayer::NORMAL_PRIORITY);

			bool isMouseOverGui() const;

		private:
			void processLayer(GuiLayer layer, float dt);
			void renderLayer(GuiLayer layer, float dt) const;

			std::unordered_map<GuiLayer, GuiList> m_guis;

			render::Renderer m_renderer;
		};
	}
}