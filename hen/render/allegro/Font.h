
#pragma once

#include "hen/io/File.h"

#include <allegro5/allegro_font.h>

#include <string>
#include <unordered_map>

namespace hen
{
	namespace allegro
	{
		class Font
		{
		public:
			Font() = default;
			Font(const Font&) = delete;
			Font(Font&&) = delete;
			~Font() { onUnload(); }

			Font& operator=(const Font&) = delete;
			Font& operator=(Font&&) = delete;

			void onLoad(const io::File& file);
			void onUnload();

			inline ALLEGRO_FONT* getHandle() const { return m_handle; }

		private:
			ALLEGRO_FONT* m_handle;
		};
	}
}