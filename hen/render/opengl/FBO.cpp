
#include "hen/render/opengl/FBO.h"

#include "hen/render/opengl/OpenGL.h"

unsigned int hen::opengl::FBO::m_boundHandle = 0;

hen::opengl::FBO::FBO()
{
	glGenFramebuffers(1, &m_handle);
}
hen::opengl::FBO::~FBO()
{
	if (m_handle != 0)
	{
		if (m_boundHandle == m_handle)
			unbind();
		glDeleteFramebuffers(1, &m_handle);
	}
}

bool hen::opengl::FBO::bind() const
{
	bool error = (m_boundHandle == m_handle || m_handle == 0 || m_boundHandle != 0);
	m_boundHandle = m_handle;
	glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
	return !error;
}
bool hen::opengl::FBO::unbind() const
{
	bool error = (m_boundHandle != m_handle);
	m_boundHandle = 0;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return !error;
}
