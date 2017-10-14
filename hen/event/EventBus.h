
#pragma once

#include "hen/event/Callback.h"
#include "hen/event/Listener.h"

#include <functional>
#include <memory>
#include <unordered_map>

namespace hen
{
	namespace event
	{
		class EventBus
		{
		public:
			EventBus() = default;
			EventBus(const EventBus&) = delete;
			EventBus(EventBus&&) = delete;
			~EventBus() = default;

			EventBus& operator=(const EventBus&) = delete;
			EventBus& operator=(EventBus&&) = delete;

			template<typename Event>
			inline Listener registerCallback(const std::function<void(Event&)>& callback)
			{
				return registerCallback(std::make_unique<Callback<Event>>(callback));
			}
			template<typename Event>
			inline Listener registerCallback(std::function<void(Event&)>&& callback)
			{
				return registerCallback(std::make_unique<Callback<Event>>(callback));
			}
			template<typename Event>
			inline Listener registerCallback(const Callback<Event>& callback)
			{
				return registerCallback(std::make_unique<Callback<Event>>(callback));
			}
			template<typename Event>
			inline Listener registerCallback(Callback<Event>&& callback)
			{
				return registerCallback(std::make_unique<Callback<Event>>(callback));
			}
			Listener registerCallback(std::unique_ptr<CallbackBase>&& callback);
			bool unregisterListener(const Listener& listener);

			template<typename Event>
			void post(Event& event) const
			{
				auto type = typeid(Event).hash_code();
				for (unsigned int i = 0; i < 6; ++i)
				{
					const auto& search = m_callbacks[i].find(type);
					if (search == m_callbacks[i].end())
						continue;
					for (const auto& callback : search->second.m_callbacks)
						static_cast<Callback<Event>*>(callback.second.get())->invoke(event);
				}
			}

		private:
			struct CallbackCollection
			{
				std::unordered_map<unsigned int, std::unique_ptr<CallbackBase>> m_callbacks;
				unsigned int m_uniqueIds = 0;
			};

			std::unordered_map<size_t, CallbackCollection> m_callbacks[6];
		};
	}
}