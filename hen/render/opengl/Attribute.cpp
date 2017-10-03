
#include "hen/render/opengl/Attribute.h"

#include "hen/render/opengl/OpenGL.h"

void hen::opengl::Attribute::bind(unsigned int size) const
{
	glVertexAttribPointer(m_index, m_count, static_cast<GLenum>(m_format), GL_FALSE, size, (const GLvoid*)m_offset);
	glEnableVertexAttribArray(m_index);
}
