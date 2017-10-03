
#include "hen/render/opengl/Texture.h"

#include "hen/render/opengl/OpenGL.h"

std::unordered_map<hen::opengl::TextureType, unsigned int> hen::opengl::Texture::m_boundHandle;

hen::opengl::Texture::Texture(TextureType type)
{
	glGenTextures(1, &m_handle);
}
hen::opengl::Texture::~Texture()
{
	if (m_handle != 0)
	{
		if (m_boundHandle[m_textureType] == m_handle)
			unbind();
		glDeleteTextures(1, &m_handle);
	}
}

bool hen::opengl::Texture::bind() const
{
	bool error = (m_boundHandle[m_textureType] == m_handle || m_handle == 0 || m_boundHandle[m_textureType] != 0);
	m_boundHandle[m_textureType] = m_handle;
	glBindTexture(static_cast<GLenum>(m_textureType), m_handle);
	return !error;
}
bool hen::opengl::Texture::unbind() const
{
	bool error = (m_boundHandle[m_textureType] != m_handle);
	m_boundHandle[m_textureType] = 0;
	glBindTexture(static_cast<GLenum>(m_textureType), 0);
	return !error;
}