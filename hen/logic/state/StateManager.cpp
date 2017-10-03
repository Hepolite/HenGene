
#include "hen/logic/state/StateManager.h"

void hen::state::StateManager::process(float dt)
{
	for (const auto& state : m_states)
		state->onProcess(dt);
	performTasks();
}

bool hen::state::StateManager::addState(std::shared_ptr<State> state)
{
	if (state == nullptr)
		return false;
	for (const auto& task : m_tasks)
		if (task.first == Task::ADD && task.second == state)
			return nullptr;
	for (const auto& s : m_states)
		if (s == state)
			return false;

	m_tasks.emplace_back(Task::ADD, state);
	return true;
}
bool hen::state::StateManager::setState(std::shared_ptr<State> state)
{
	clearStates();
	return addState(state);
}
bool hen::state::StateManager::removeState(std::shared_ptr<State> state)
{
	if (state == nullptr)
		return false;
	for (const auto& task : m_tasks)
		if (task.first == Task::REMOVE && task.second == state)
			return false;

	m_tasks.emplace_back(Task::REMOVE, state);
	return true;
}
void hen::state::StateManager::clearStates()
{
	m_tasks.emplace_back(Task::CLEAR, nullptr);
}

void hen::state::StateManager::performTasks()
{
	for (const auto& task : m_tasks)
	{
		switch (task.first)
		{
		case Task::ADD:
			m_states.emplace_back(task.second);
			task.second->onInitialize();
			break;

		case Task::REMOVE:
			for (auto& it = m_states.begin(); it != m_states.end(); ++it)
			{
				if (*it == task.second)
				{
					task.second->onDeinitialize();
					m_states.erase(it);
					break;
				}
			}
			break;

		case Task::CLEAR:
			for (auto& state : m_states)
				state->onDeinitialize();
			m_states.clear();
			break;
		}
	}
	m_tasks.clear();
}
