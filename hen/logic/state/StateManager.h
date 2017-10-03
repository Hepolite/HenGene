
#pragma once

#include "hen/logic/state/State.h"

#include <memory>
#include <vector>

namespace hen
{
	namespace state
	{
		class StateManager
		{
		public:
			StateManager() = default;
			StateManager(const StateManager&) = delete;
			StateManager(StateManager&&) = delete;
			~StateManager() = default;

			StateManager& operator=(const StateManager&) = delete;
			StateManager& operator=(StateManager&&) = delete;

			void process(float dt);

			template<class State> inline bool addState() { return addState(std::make_shared<State>()); }
			template<class State> inline bool setState() { return setState(std::make_shared<State>()); }
			bool addState(std::shared_ptr<State> state);
			bool setState(std::shared_ptr<State> state);
			bool removeState(std::shared_ptr<State>);
			void clearStates();

		private:
			enum class Task { ADD, REMOVE, CLEAR };

			void performTasks();

			std::vector<std::shared_ptr<State>> m_states;
			std::vector<std::pair<Task, std::shared_ptr<State>>> m_tasks;
		};
	}
}