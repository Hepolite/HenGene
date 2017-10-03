
#include "hen/render/uniform/UniformBlockManager.h"

hen::uniform::UBO& hen::uniform::UniformBlockManager::create(const std::string& name)
{
	const auto& result = m_ubos.find(name);
	if (result != m_ubos.end())
		throw std::invalid_argument("Uniform Buffer Object " + name + " already exists");

	const auto& ubo = m_ubos.emplace(name, m_nextPortIndex);
	m_ports[name] = m_nextPortIndex;
	m_nextPortIndex++;
	return ubo.first->second;
}
bool hen::uniform::UniformBlockManager::has(const std::string& name) const
{
	return m_ubos.find(name) != m_ubos.end();
}
const hen::uniform::UBO& hen::uniform::UniformBlockManager::get(const std::string& name) const
{
	const auto& result = m_ubos.find(name);
	if (result == m_ubos.end())
		throw std::invalid_argument("Uniform Buffer Object " + name + " does not exist");
	return result->second;
}
