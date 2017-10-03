
#pragma once

#include "hen/event/Priority.h"

#include <functional>
#include <typeinfo>

namespace hen
{
	namespace event
	{
		class CallbackBase
		{
		public:
			CallbackBase(Priority priority, size_t type)
				: m_priority(priority), m_type(type)
			{}
			virtual ~CallbackBase() = default;

			inline Priority getPriority() const { return m_priority; }
			inline size_t getType() const { return m_type; }

		private:
			Priority m_priority;
			size_t m_type;
		};

		template<typename Event, Priority priority = Priority::NORMAL>
		class Callback : public CallbackBase
		{
		public:
			Callback(const std::function<void(Event&)>& callback)
				: CallbackBase(priority, typeid(Event).hash_code()), m_callback(callback)
			{}
			virtual ~Callback() = default;

			inline void invoke(Event& event) { m_callback(event); }

		private:
			std::function<void(Event&)> m_callback;
		};
	}
}