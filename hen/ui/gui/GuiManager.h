
#pragma once

#include "hen/event/Listener.h"
#include "hen/render/Renderer.h"
#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/ui/gui/internal/GuiLayer.h"

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace hen
{
	namespace gui
	{
		class GuiManager
		{
			using GuiPtr = std::unique_ptr<GuiBase>;
			using GuiList = std::vector<GuiPtr>;

		public:
			GuiManager();
			GuiManager(const GuiManager&) = delete;
			GuiManager(GuiManager&&) = delete;
			~GuiManager();

			GuiManager& operator=(const GuiManager&) = delete;
			GuiManager& operator=(GuiManager&&) = delete;

			void initialize();
			void process(float dt);
			void render(float dt) const;

			GuiBase* open(GuiLayer layer = GuiLayer::NORMAL_PRIORITY);
			void close(GuiBase* gui);

			bool isMouseOverGui() const;

		private:
			void processLayer(GuiLayer layer, float dt);
			void renderLayer(GuiLayer layer, float dt) const;

			void openGuis();
			void closeGuis();

			void onResizeScreen(int width, int height);

			std::unordered_map<GuiLayer, GuiList> m_guis;
			std::unordered_set<GuiBase*> m_guisToClose;
			std::vector<GuiPtr> m_guisToOpen;

			event::Listener m_listener;
			render::Renderer m_renderer;
		};
	}
}