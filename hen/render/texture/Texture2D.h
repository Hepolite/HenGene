
#pragma once

#include "hen/render/opengl/Texture.h"

#include <allegro5/bitmap.h>

namespace hen
{
	namespace texture
	{
		class Texture2D
		{
		public:
			Texture2D() {}
			Texture2D(const Texture2D&) = delete;
			Texture2D(Texture2D&&) = delete;
			~Texture2D() {}

			Texture2D& operator=(const Texture2D&) = delete;
			Texture2D& operator=(Texture2D&&) = delete;

			inline bool bind() const { return m_underlying.bind(); }
			inline bool unbind() const { return m_underlying.unbind(); }

			inline unsigned int getHandle() const { return m_underlying.getHandle(); }

		private:
			opengl::Texture m_underlying{ opengl::TextureType::TEXTURE_2D };

			int m_width = 0;
			int m_height = 0;
		};
	}
}