
#pragma once

#include "hen/render/opengl/Flags.h"

#include <unordered_map>

namespace hen
{
	namespace opengl
	{
		class Texture
		{
		public:
			Texture(TextureType type);
			Texture(const Texture&) = delete;
			Texture(Texture&&) = delete;
			~Texture();

			Texture& operator=(const Texture&) = delete;
			Texture& operator=(Texture&&) = delete;

			bool bind() const;
			bool unbind() const;

			inline unsigned int getHandle() const { return m_handle; }

		private:
			static std::unordered_map<TextureType, unsigned int> m_boundHandle;

			TextureType m_textureType = TextureType::TEXTURE_2D;
			unsigned int m_handle;
		};
	}
}