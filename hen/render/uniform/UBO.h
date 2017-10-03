
#pragma once

#include "hen/render/opengl/VBO.h"

#include <string>
#include <unordered_map>

namespace hen
{
	namespace uniform
	{
		class UBO
		{
		public:
			UBO(unsigned int port) : m_port(port) {}
			UBO(const UBO&) = delete;
			UBO(UBO&&) = delete;
			~UBO() = default;

			UBO& operator=(const UBO&) = delete;
			UBO& operator=(UBO&&) = delete;

			template<typename T>
			inline bool addField(const std::string& name) { return addField(name, sizeof(T)); }
			template<typename T>
			inline bool setField(const std::string& name, const T& data) const { return setField(name, sizeof(T), &data[0]); }
			inline bool setField(const std::string& name, const float& data) const { return setField(name, sizeof(float), &data); }
			template<typename T>
			inline bool getField(const std::string& name, T& data) const { return getField(name, sizeof(T), &data[0]); }
			inline bool getField(const std::string& name, float& data) const { return getField(name, sizeof(float), &data); }

			bool build();

			inline bool bind() const { return m_underlying.bind(); }
			inline bool unbind() const { return m_underlying.unbind(); }

			inline unsigned int getHandle() const { return m_underlying.getHandle(); }
			inline unsigned int getSize() const { return m_size; }

		private:
			bool addField(const std::string& name, unsigned int size);
			bool setField(const std::string& name, unsigned int size, const void* data) const;
			bool getField(const std::string& name, unsigned int size, void* data) const;

			opengl::VBO m_underlying{ opengl::BufferType::UNIFORM_BUFFER };

			std::unordered_map<std::string, unsigned int> m_offsets;
			std::unordered_map<std::string, unsigned int> m_sizes;
			unsigned int m_size = 0;
			unsigned int m_port = 0;
			bool m_isBuilt = false;
		};
	}
}