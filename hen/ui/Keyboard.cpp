
#include "hen/ui/Keyboard.h"

#include "hen/core/Core.h"
#include "hen/event/EventBus.h"
#include "hen/event/events/Keyboard.h"

hen::ui::Keyboard::Keyboard()
{
	m_characters = al_ustr_new("");
}
hen::ui::Keyboard::~Keyboard()
{
	al_ustr_free(m_characters);
}

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
	m_character = bus.registerCallback<events::KeyUnichar>([this](const events::KeyUnichar& event)
	{
		if (event.getUnichar() >= 32)
			al_ustr_append_chr(m_characters, event.getUnichar());
	});
}
void hen::ui::Keyboard::deinitialize()
{
	auto& bus = Core::getEventBus();
	bus.unregisterListener(m_press);
	bus.unregisterListener(m_release);
	bus.unregisterListener(m_character);
}

void hen::ui::Keyboard::process()
{
	m_pressed.clear();
	m_released.clear();

	al_ustr_truncate(m_characters, 0);
}
