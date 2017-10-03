
#include "hen/event/EventBus.h"

hen::event::Listener hen::event::EventBus::registerCallback(std::unique_ptr<CallbackBase>&& callback)
{
	Priority priority = callback->getPriority();
	size_t type = callback->getType();

	int index = static_cast<int>(priority);
	auto& collection = m_callbacks[index][type];
	unsigned int id = ++collection.m_uniqueIds;
	collection.m_callbacks.emplace(id, std::move(callback));

	return Listener{ id, priority, type };
}
bool hen::event::EventBus::unregisterListener(const Listener& listener)
{
	if (listener.getID() == 0)
		return false;

	int index = static_cast<int>(listener.getPriority());
	const auto& search = m_callbacks[index].find(listener.getType());
	if (search == m_callbacks[index].end())
		return false;
	
	auto& collection = search->second.m_callbacks;
	return collection.erase(listener.getID()) > 0;
}
