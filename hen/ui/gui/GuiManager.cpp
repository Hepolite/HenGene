
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
	processLayer(GuiLayer::HIGHEST_PRIORITY, dt);
	processLayer(GuiLayer::HIGH_PRIORITY, dt);
	processLayer(GuiLayer::NORMAL_PRIORITY, dt);
	processLayer(GuiLayer::LOW_PRIORITY, dt);
	processLayer(GuiLayer::LOWEST_PRIORITY, dt);
}
void hen::gui::GuiManager::processLayer(GuiLayer layer, float dt)
{
	const auto& it = m_guis.find(layer);
	if (it == m_guis.end())
		return;
	for (auto& gui : it->second)
		gui->process(dt);
}
void hen::gui::GuiManager::render(float dt) const
{
	renderLayer(GuiLayer::LOWEST_PRIORITY, dt);
	renderLayer(GuiLayer::LOW_PRIORITY, dt);
	renderLayer(GuiLayer::NORMAL_PRIORITY, dt);
	renderLayer(GuiLayer::HIGH_PRIORITY, dt);
	renderLayer(GuiLayer::HIGHEST_PRIORITY, dt);
}

void hen::gui::GuiManager::renderLayer(GuiLayer layer, float dt) const
{
	const auto& it = m_guis.find(layer);
	if (it == m_guis.end())
		return;
	for (const auto& gui : it->second)
		gui->render(dt);
}

hen::gui::GuiBase* hen::gui::GuiManager::open(GuiLayer layer)
{
	auto gui = std::make_unique<GuiBase>(layer);
	const auto ptr = gui.get();
	m_guis[layer].push_back(std::move(gui));
	return ptr;
}
void hen::gui::GuiManager::close(GuiBase* gui)
{
	if (gui == nullptr)
		return;
	auto& map = m_guis[gui->getLayer()];
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		if (it->get() == gui)
		{
			std::swap(*it, map.back());
			map.pop_back();
			return;
		}
	}
	if (map.empty())
		m_guis.erase(gui->getLayer());
}