
#pragma once

#include "hen/render/opengl/Flags.h"

namespace hen
{
	namespace opengl
	{
		class Attribute
		{
		public:
			Attribute() = default;
			/*
			Specifies an attribute of the vertex in a shader

			@param index The index of the attribute in a shader
			@param count The number of of values associated with the attribute (3 for vec3, 1 for float, etc)
			@param format The format of the internal data (BYTE, UNSIGNED_BYTE, SHORT, UNSIGNED_SHORT, and FLOAT are accepted)
			@param offset The offset of the data given in bytes
			*/
			Attribute(unsigned int index, Format format, int count, unsigned int offset)
				: m_index(index), m_format(format), m_count(count), m_offset(offset)
			{}
			~Attribute() = default;

			void bind(unsigned int size) const;

		private:
			unsigned int m_index = 0;
			unsigned int m_offset = 0;
			Format m_format = Format::FLOAT;
			int m_count = 0;
		};
	}
}