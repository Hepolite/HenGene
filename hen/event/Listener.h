
#pragma once

#include "hen/event/Priority.h"

namespace hen
{
	namespace event
	{
		class Listener
		{
		public:
			Listener() = default;
			Listener(unsigned int id, Priority priority, size_t type)
				: m_id(id), m_priority(priority), m_type(type)
			{}
			~Listener() = default;

			inline unsigned int getID() const { return m_id; }
			inline Priority getPriority() const { return m_priority; }
			inline size_t getType() const { return m_type; }

		private:
			unsigned int m_id = 0;
			Priority m_priority = Priority::NORMAL;
			size_t m_type = 0;
		};
	}
}