
#pragma once

#include "hen/event/Listener.h"

#include <vector>

namespace hen
{
	namespace gui
	{
		class ComponentListener
		{
		public:
			ComponentListener();
			ComponentListener(const ComponentListener&) = delete;
			ComponentListener(ComponentListener&&) = delete;
			~ComponentListener();

			ComponentListener& operator=(const ComponentListener&) = delete;
			ComponentListener& operator=(ComponentListener&&) = delete;

			inline void add(event::Listener listener) { m_listeners.push_back(listener); }
			inline const std::vector<event::Listener>& get() { return m_listeners; }

		private:
			std::vector<event::Listener> m_listeners;
		};
	}
}