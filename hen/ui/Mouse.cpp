
#include "hen/ui/Mouse.h"

#include "hen/core/Core.h"
#include "hen/event/EventBus.h"
#include "hen/event/events/Mouse.h"
#include "hen/ui/Display.h"

#include <allegro5/mouse.h>

void hen::ui::Mouse::initialize()
{
	auto& bus = Core::getEventBus();
	m_move = bus.registerCallback<events::MouseMove>([this](const events::MouseMove& event)
	{
		m_pos = event.getPos();
		m_delta += event.getDelta();
	});
	m_press = bus.registerCallback<events::MousePress>([this](const events::MousePress& event)
	{
		m_pressed.insert(event.getButton());
		m_held.insert(event.getButton());
	});
	m_release = bus.registerCallback<events::MouseRelease>([this](const events::MouseRelease& event)
	{
		m_released.insert(event.getButton());
		m_held.erase(event.getButton());
	});
}
void hen::ui::Mouse::deinitialize()
{
	auto& bus = Core::getEventBus();
	bus.unregisterListener(m_move);
	bus.unregisterListener(m_press);
	bus.unregisterListener(m_release);
}

void hen::ui::Mouse::process()
{
	m_pressed.clear();
	m_released.clear();
	m_delta = glm::vec4{};
}

void hen::ui::Mouse::setPos(const glm::ivec2& pos) const
{
	al_set_mouse_xy(hen::Core::getDisplay().getHandle(), pos.x, pos.y);
}
