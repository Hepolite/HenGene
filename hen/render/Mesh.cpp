
#include "hen/render/Mesh.h"

#include "hen/render/opengl/OpenGL.h"

bool hen::render::MeshBase::build(unsigned int indices, unsigned int vertices, const void* indiceData, const void* vertexData)
{
	if (m_isBuilt)
		return false;
	m_isBuilt = true;
	m_indices = indices;

	m_vao.bind();

	m_vertexVBO.bind();
	m_vertexVBO.bufferData(vertices * m_size, vertexData);
	for (const auto& attribute : m_attributes)
		attribute.bind(m_size);

	m_indiceVBO.bind();
	m_indiceVBO.bufferData(indices * sizeof(unsigned int), indiceData);

	m_vao.unbind();
	return true;
}
void hen::render::MeshBase::clear()
{
	m_isBuilt = false;
	m_indices = 0;
	m_attributes.clear();
}

void hen::render::MeshBase::render() const
{
	if (!m_isBuilt)
		return;

	m_vao.bind();
	glDrawElements(static_cast<GLenum>(m_renderMode), m_indices, GL_UNSIGNED_INT, nullptr);
}
