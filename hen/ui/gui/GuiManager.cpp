
#include "hen/ui/gui/GuiManager.h"

#include "hen/core/Core.h"
#include "hen/render/RenderCore.h"

hen::gui::GuiManager::GuiManager() {}
hen::gui::GuiManager::~GuiManager()
{
	Core::getRenderCore().deleteRenderer(m_renderer);
}

void hen::gui::GuiManager::initialize()
{
	m_renderer = Core::getRenderCore().addRenderer(render::RenderLayer::SCREEN, [this](float dt) { render(dt); });
}

void hen::gui::GuiManager::process(float dt)
{
	processLayer(GuiLayer::HIGH_PRIORITY, dt);
	processLayer(GuiLayer::NORMAL_PRIORITY, dt);
	processLayer(GuiLayer::LOW_PRIORITY, dt);
}
void hen::gui::GuiManager::processLayer(GuiLayer layer, float dt)
{
	const auto& it = m_guis.find(layer);
	if (it == m_guis.end())
		return;
	for (auto& gui : it->second)
		gui->onProcess(dt);
}
void hen::gui::GuiManager::render(float dt) const
{
	renderLayer(GuiLayer::LOW_PRIORITY, dt);
	renderLayer(GuiLayer::NORMAL_PRIORITY, dt);
	renderLayer(GuiLayer::HIGH_PRIORITY, dt);
}

void hen::gui::GuiManager::renderLayer(GuiLayer layer, float dt) const
{
	const auto& it = m_guis.find(layer);
	if (it == m_guis.end())
		return;
	for (const auto& gui : it->second)
		gui->onRender(dt);
}

void hen::gui::GuiManager::add(Gui* gui, GuiLayer layer)
{
	if (gui != nullptr)
		m_guis[layer].push_back(gui);
}
void hen::gui::GuiManager::remove(Gui* gui, GuiLayer layer)
{
	if (gui == nullptr)
		return;
	auto& map = m_guis[layer];
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		if (*it == gui)
		{
			std::swap(*it, map.back());
			map.pop_back();
			return;
		}
	}
}