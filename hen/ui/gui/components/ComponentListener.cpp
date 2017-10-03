
#include "hen/ui/gui/components/ComponentListener.h"

#include "hen/core/Core.h"
#include "hen/event/EventBus.h"

hen::gui::ComponentListener::ComponentListener(){}
hen::gui::ComponentListener::~ComponentListener()
{
	for (const auto& listener : m_listeners)
		Core::getEventBus().unregisterListener(listener);
}
