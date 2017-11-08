
#include "hen/ui/gui/GuiManager.h"

#include "hen/core/Core.h"
#include "hen/event/EventBus.h"
#include "hen/event/events/Display.h"
#include "hen/render/RenderCore.h"

hen::gui::GuiManager::GuiManager() {}
hen::gui::GuiManager::~GuiManager()
{
	Core::getEventBus().unregisterListener(m_listener);
	Core::getRenderCore().deleteRenderer(m_renderer);
}

void hen::gui::GuiManager::initialize()
{
	m_listener = Core::getEventBus().registerCallback<events::DisplayResize>(
		[this](const events::DisplayResize& event) { onResizeScreen(event.getWidth(), event.getHeight()); }
	);
	m_renderer = Core::getRenderCore().addRenderer(render::RenderLayer::SCREEN, [this](float dt) { render(dt); });
}

void hen::gui::GuiManager::process(float dt)
{
	openGuis();
	processLayer(GuiLayer::HIGHEST_PRIORITY, dt);
	processLayer(GuiLayer::HIGH_PRIORITY, dt);
	processLayer(GuiLayer::NORMAL_PRIORITY, dt);
	processLayer(GuiLayer::LOW_PRIORITY, dt);
	processLayer(GuiLayer::LOWEST_PRIORITY, dt);
	closeGuis();
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
	m_guisToOpen.emplace_back(std::make_unique<GuiBase>(layer));
	return m_guisToOpen.back().get();
}
void hen::gui::GuiManager::openGuis()
{
	for (auto& gui : m_guisToOpen)
		m_guis[gui->getLayer()].emplace_back(std::move(gui));
	m_guisToOpen.clear();
}
void hen::gui::GuiManager::close(GuiBase* gui)
{
	if (gui != nullptr)
		m_guisToClose.insert(gui);
}
void hen::gui::GuiManager::closeGuis()
{
	for (auto gui : m_guisToClose)
	{
		auto& map = m_guis[gui->getLayer()];
		for (auto it = map.begin(); it != map.end(); ++it)
		{
			if (it->get() == gui)
			{
				std::swap(*it, map.back());
				map.pop_back();
				break;
			}
		}
		if (map.empty())
			m_guis.erase(gui->getLayer());
	}
	m_guisToClose.clear();
}

void hen::gui::GuiManager::onResizeScreen(int width, int height)
{
	const glm::vec2 size{ width, height };

	for (auto& list : m_guis)
	for (auto& gui : list.second)
	{
		auto& widget = gui->getWidget();
		widget.m_size.setMaxSize(size);
		widget.m_size.setMinSize(size);
	}
}
