
#pragma once

#include "hen/ui/gui/internal/GuiBase.h"
#include "hen/ui/gui/internal/GuiLayer.h"
#include "hen/render/Renderer.h"

#include <memory>
#include <unordered_map>

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

			std::unordered_map<GuiLayer, GuiList> m_guis;

			render::Renderer m_renderer;
		};
	}
}