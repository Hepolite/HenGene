
#include "hen/render/opengl/VBO.h"

#include "hen/render/opengl/OpenGL.h"

std::unordered_map<hen::opengl::BufferType, unsigned int> hen::opengl::VBO::m_boundHandle;

hen::opengl::VBO::VBO(BufferType bufferType)
	: m_bufferType(bufferType)
{
	glGenBuffers(1, &m_handle);
}
hen::opengl::VBO::~VBO()
{
	if (m_handle != 0)
	{
		if (m_boundHandle[m_bufferType] == m_handle)
			unbind();
		glDeleteBuffers(1, &m_handle);
	}
}

bool hen::opengl::VBO::bind() const
{
	bool error = (m_boundHandle[m_bufferType] == m_handle || m_handle == 0 || m_boundHandle[m_bufferType] != 0);
	m_boundHandle[m_bufferType] = m_handle;
	glBindBuffer(static_cast<GLenum>(m_bufferType), m_handle);
	return !error;
}
bool hen::opengl::VBO::unbind() const
{
	bool error = (m_boundHandle[m_bufferType] != m_handle);
	m_boundHandle[m_bufferType] = 0;
	glBindBuffer(static_cast<GLenum>(m_bufferType), 0);
	return !error;
}

bool hen::opengl::VBO::bufferData(int byteCount, const void* data) const
{
	if (m_boundHandle[m_bufferType] != m_handle || byteCount <= 0 || (data == nullptr && m_reservedSpace))
		return false;
	m_reservedSpace = true;
	glBufferData(static_cast<GLenum>(m_bufferType), byteCount, data, GL_STATIC_DRAW);
	return true;
}
bool hen::opengl::VBO::bufferSubData(int byteCount, const void* data, int offset) const
{
	if (m_boundHandle[m_bufferType] != m_handle || byteCount <= 0 || offset < 0 || data == nullptr || !m_reservedSpace)
		return false;
	glBufferSubData(static_cast<GLenum>(m_bufferType), offset, byteCount, data);
	return true;
}
bool hen::opengl::VBO::getSubData(int byteCount, void* data, int offset) const
{
	if (m_boundHandle[m_bufferType] != m_handle || byteCount <= 0 || offset < 0 || data == nullptr || !m_reservedSpace)
		return false;
	glGetBufferSubData(static_cast<GLenum>(m_bufferType), offset, byteCount, data);
	return true;
}
