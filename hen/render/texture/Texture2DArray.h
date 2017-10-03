
#pragma once

#include "hen/io/File.h"
#include "hen/render/opengl/Texture.h"

#include <allegro5/bitmap.h>

#include <string>
#include <unordered_map>
#include <vector>

namespace hen
{
	namespace texture
	{
		class Texture2DArray
		{
		public:
			Texture2DArray();
			Texture2DArray(const Texture2DArray&) = delete;
			Texture2DArray(Texture2DArray&&) = delete;
			~Texture2DArray();

			Texture2DArray& operator=(const Texture2DArray&) = delete;
			Texture2DArray& operator=(Texture2DArray&&) = delete;

			unsigned int attach(const io::File& file);
			unsigned int attach(ALLEGRO_BITMAP* bitmap);
			bool build();

			inline bool bind() const { return m_underlying.bind(); }
			inline bool unbind() const { return m_underlying.unbind(); }

			inline unsigned int getHandle() const { return m_underlying.getHandle(); }

		private:
			void clear();

			opengl::Texture m_underlying{ opengl::TextureType::TEXTURE_2D_ARRAY };

			std::unordered_map<std::string, unsigned int> m_fileHandles;
			std::vector<ALLEGRO_BITMAP*> m_parentBitmaps;
			std::vector<ALLEGRO_BITMAP*> m_bitmaps;

			int m_width = 0;
			int m_height = 0;
			int m_depth = 0;
			bool m_isBuilt = false;
		};
	}
}