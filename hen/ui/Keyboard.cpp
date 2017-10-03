
#include "hen/ui/Keyboard.h"

#include "hen/core/Core.h"
#include "hen/event/EventBus.h"
#include "hen/event/events/Keyboard.h"

void hen::ui::Keyboard::initialize()
{
	auto& bus = Core::getEventBus();
	m_press = bus.registerCallback<events::KeyPress>([this](const events::KeyPress& event)
	{
		m_pressed.insert(event.getKey());
		m_held.insert(event.getKey());
	});
	m_release = bus.registerCallback<events::KeyRelease>([this](const events::KeyRelease& event)
	{
		m_released.insert(event.getKey());
		m_held.erase(event.getKey());
	});
}
void hen::ui::Keyboard::deinitialize()
{
	auto& bus = Core::getEventBus();
	bus.unregisterListener(m_press);
	bus.unregisterListener(m_release);
}

void hen::ui::Keyboard::process()
{
	m_pressed.clear();
	m_released.clear();
}
