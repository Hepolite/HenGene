
#pragma once

#include "hen/render/opengl/Attribute.h"
#include "hen/render/opengl/Flags.h"
#include "hen/render/opengl/VAO.h"
#include "hen/render/opengl/VBO.h"

#include <vector>

namespace hen
{
	namespace render
	{
		class MeshBase
		{
		public:
			inline void setRenderMode(opengl::RenderMode renderMde) { m_renderMode = renderMde; }
			inline void addAttribute(const opengl::Attribute& attribute) { m_attributes.push_back(attribute); }

			void render() const;

		protected:
			MeshBase() = default;
			MeshBase(unsigned int size) : m_size(size) {}
			MeshBase(const MeshBase&) = delete;
			MeshBase(MeshBase&&) = delete;
			virtual ~MeshBase() = default;

			MeshBase& operator=(const MeshBase&) = delete;
			MeshBase& operator=(MeshBase&&) = delete;

			bool build(unsigned int indices, unsigned int vertices, const void* indiceData, const void* vertexData);
			void clear();

		private:
			opengl::VAO m_vao;
			opengl::VBO m_vertexVBO{ opengl::BufferType::ARRAY_BUFFER };
			opengl::VBO m_indiceVBO{ opengl::BufferType::ELEMENT_ARRAY_BUFFER };

			opengl::RenderMode m_renderMode = opengl::RenderMode::TRIANGLES;
			std::vector<opengl::Attribute> m_attributes;

			unsigned int m_size = 0;
			unsigned int m_indices = 0;
			bool m_isBuilt = false;
		};

		template<typename Vertex>
		class Mesh : public MeshBase
		{
		public:
			Mesh() : MeshBase(sizeof(Vertex)) {}
			virtual ~Mesh() = default;

			inline std::vector<unsigned int>& getIndiceData() { return m_indices; }
			inline std::vector<Vertex>& getVertexData() { return m_vertices; }

			bool build()
			{
				if (m_indices.size() == 0 || m_vertices.size() == 0)
					return false;
				return MeshBase::build(m_indices.size(), m_vertices.size(), &m_indices[0], &m_vertices[0]);
			}
			void clear()
			{
				m_indices.clear();
				m_vertices.clear();
				MeshBase::clear();
			}

		private:
			std::vector<unsigned int> m_indices;
			std::vector<Vertex> m_vertices;
		};
	}
}