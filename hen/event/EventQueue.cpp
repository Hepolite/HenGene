
#include "hen/event/EventQueue.h"

#include "hen/core/Core.h"
#include "hen/event/EventBus.h"

#include "hen/event/events/Display.h"
#include "hen/event/events/Keyboard.h"
#include "hen/event/events/Mouse.h"

#include <allegro5/display.h>
#include <Log.h>

hen::event::EventQueue::EventQueue()
{
	m_handle = al_create_event_queue();
}
hen::event::EventQueue::~EventQueue()
{
	if (m_handle != nullptr)
		al_destroy_event_queue(m_handle);
}

void hen::event::EventQueue::process() const
{
	const auto& bus = Core::getEventBus();

	ALLEGRO_EVENT event;
	while (al_get_next_event(m_handle, &event))
	{
		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			bus.post(events::DisplayClose{});
			break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			al_acknowledge_resize(event.display.source);
			bus.post(events::DisplayResize{ event.display.width, event.display.height });
			break;

		case ALLEGRO_EVENT_KEY_DOWN:
			bus.post(events::KeyPress{ event.keyboard.keycode, event.keyboard.modifiers });
			break;
		case ALLEGRO_EVENT_KEY_UP:
			bus.post(events::KeyRelease{ event.keyboard.keycode, event.keyboard.modifiers });
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			bus.post(events::KeyUnichar{ event.keyboard.unichar, event.keyboard.modifiers });
			break;

		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
			bus.post(events::MouseEnterDisplay{});
			break;
		case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
			bus.post(events::MouseLeaveDisplay{});
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			bus.post(events::MousePress{
				event.mouse.button == (MOUSE_LEFT | MOUSE_RIGHT) ? MOUSE_MIDDLE : event.mouse.button,
				glm::vec4 { event.mouse.x, event.mouse.y, event.mouse.z, event.mouse.w }
			});
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			bus.post(events::MouseRelease{
				event.mouse.button == (MOUSE_LEFT | MOUSE_RIGHT) ? MOUSE_MIDDLE : event.mouse.button,
				glm::vec4 { event.mouse.x, event.mouse.y, event.mouse.z, event.mouse.w }
			});
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			bus.post(events::MouseMove{
				glm::vec4{ event.mouse.dx, event.mouse.dy, event.mouse.dz, event.mouse.dw },
				glm::vec4{ event.mouse.x, event.mouse.y, event.mouse.z, event.mouse.w }
			});
			break;
		case ALLEGRO_EVENT_MOUSE_WARPED:
			break;

		default:
			LOG_WARNING << "Unhandled Allegro event type detected: " << event.type;
		}
	}
}

bool hen::event::EventQueue::registerSource(ALLEGRO_EVENT_SOURCE* source)
{
	if (m_handle == nullptr || source == nullptr)
		return false;
	if (m_sources.find(source) != m_sources.end())
	{
		LOG_WARNING << "Attempted to register an event source which has already been registered";
		return false;
	}
	al_register_event_source(m_handle, source);
	m_sources.emplace(source);
	return true;
}
bool hen::event::EventQueue::unregisterSource(ALLEGRO_EVENT_SOURCE* source)
{
	if (m_handle == nullptr || source == nullptr || m_sources.find(source) == m_sources.end())
		return false;
	al_unregister_event_source(m_handle, source);
	m_sources.erase(source);
	return true;
}
