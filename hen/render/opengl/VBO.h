
#pragma once

#include "hen/render/opengl/Flags.h"

#include <unordered_map>

namespace hen
{
	namespace opengl
	{
		class VBO
		{
		public:
			VBO(BufferType bufferType);
			VBO(const VBO&) = delete;
			VBO(VBO&&) = delete;
			~VBO();

			VBO& operator=(const VBO&) = delete;
			VBO& operator=(VBO&&) = delete;

			bool bind() const;
			bool unbind() const;

			inline bool reserve(int byteCount) const { return bufferData(byteCount, nullptr); }
			bool bufferData(int byteCount, const void* data) const;
			bool bufferSubData(int byteCount, const void* data, int offset) const;
			
			bool getSubData(int byteCount, void* data, int offset) const;

			inline unsigned int getHandle() const { return m_handle; }

		private:
			static std::unordered_map<BufferType, unsigned int> m_boundHandle;

			BufferType m_bufferType = BufferType::ARRAY_BUFFER;
			unsigned int m_handle = 0;
			mutable bool m_reservedSpace = false;
		};
	}
}