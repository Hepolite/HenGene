
#include "hen/render/uniform/UBO.h"

#include "hen/render/opengl/OpenGL.h"

#include <Log.h>

bool hen::uniform::UBO::addField(const std::string& name, unsigned int size)
{
	if (m_isBuilt || m_offsets.find(name) != m_offsets.end())
		return false;
	m_offsets[name] = m_size;
	m_sizes[name] = size;
	m_size += size;
	return true;
}
bool hen::uniform::UBO::setField(const std::string& name, unsigned int size, const void* data) const
{
	if (!m_isBuilt)
		return false;
	const auto& offset = m_offsets.find(name);
	if (offset == m_offsets.end() || m_sizes.find(name)->second != size)
	{
		LOG(plog::warning) << "Field " << name << " either does not exist or wrong size " << size;
		return false;
	}
	bind();
	return m_underlying.bufferSubData(size, data, offset->second);
}
bool hen::uniform::UBO::getField(const std::string& name, unsigned int size, void* data) const
{
	if (!m_isBuilt)
		return false;
	const auto& offset = m_offsets.find(name);
	if (offset == m_offsets.end() || m_sizes.find(name)->second != size)
	{
		LOG(plog::warning) << "Field " << name << " either does not exist or wrong size " << size;
		return false;
	}
	bind();
	return m_underlying.getSubData(size, data, offset->second);
}

bool hen::uniform::UBO::build()
{
	if (m_isBuilt || m_size == 0)
		return false;
	m_isBuilt = true;
	bind();
	bool result = m_underlying.reserve(m_size);
	if (result)
		glBindBufferBase(GL_UNIFORM_BUFFER, m_port, getHandle());
	unbind();
	return result;
}
