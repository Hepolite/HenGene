
#pragma once

namespace hen
{
	namespace opengl
	{
		/* Types of buffer objects; used for VBOs and VAOs */
		enum class BufferType : unsigned int
		{
			ARRAY_BUFFER			= 0x8892,
			ELEMENT_ARRAY_BUFFER	= 0x8893,
			UNIFORM_BUFFER			= 0x8A11,
		};

		/* Format of OpenGL data */
		enum class Format : unsigned int
		{
			BYTE					= 0x1400,
			UNSIGNED_BYTE			= 0x1401,
			SHORT					= 0x1402,
			UNSIGNED_SHORT			= 0x1403,
			INT						= 0x1404,
			UNSIGNED_INT			= 0x1405,
			FLOAT					= 0x1406,
			DOUBLE					= 0x140A,
		};

		/* How geometry should be rendered */
		enum class RenderMode : unsigned int
		{
			POINTS					= 0x0000,
			LINES					= 0x0001,
			LINE_LOOP				= 0x0002,
			LINE_STRIP				= 0x0003,
			TRIANGLES				= 0x0004,
			TRIANGLE_STRIP			= 0x0005,
			TRIANGLE_FAN			= 0x0006,
			QUADS					= 0x0007,
			QUAD_STRIP				= 0x0008,
			POLYGON					= 0x0009,
		};

		/* Various types of textures */
		enum class TextureType : unsigned int
		{
			TEXTURE_2D				= 0x0DE1,
			TEXTURE_2D_ARRAY		= 0x8C1A,
		};
	}
}