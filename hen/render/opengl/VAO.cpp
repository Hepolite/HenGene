
#include "hen/render/opengl/VAO.h"

#include "hen/render/opengl/OpenGL.h"

unsigned int hen::opengl::VAO::m_boundHandle = 0;

hen::opengl::VAO::VAO()
{
	glGenVertexArrays(1, &m_handle);
}
hen::opengl::VAO::~VAO()
{
	if (m_handle != 0)
	{
		if (m_boundHandle == m_handle)
			unbind();
		glDeleteVertexArrays(1, &m_handle);
	}
}

bool hen::opengl::VAO::bind() const
{
	bool error = (m_boundHandle == m_handle || m_handle == 0 || m_boundHandle != 0);
	m_boundHandle = m_handle;
	glBindVertexArray(m_handle);
	return !error;
}
bool hen::opengl::VAO::unbind() const
{
	bool error = (m_boundHandle != m_handle);
	m_boundHandle = 0;
	glBindVertexArray(0);
	return !error;
}