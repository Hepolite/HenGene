
#pragma once

#include <allegro5/events.h>

#include <unordered_set>

namespace hen
{
	namespace event
	{
		class EventQueue
		{
		public:
			EventQueue();
			EventQueue(const EventQueue&) = delete;
			EventQueue(EventQueue&&) = delete;
			~EventQueue();

			EventQueue& operator=(const EventQueue&) = delete;
			EventQueue& operator=(EventQueue&&) = delete;

			void process() const;

			bool registerSource(ALLEGRO_EVENT_SOURCE* source);
			bool unregisterSource(ALLEGRO_EVENT_SOURCE* source);

		private:
			ALLEGRO_EVENT_QUEUE* m_handle;
			std::unordered_set<ALLEGRO_EVENT_SOURCE*> m_sources;
		};
	}
}