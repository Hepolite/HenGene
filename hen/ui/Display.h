
#pragma once

#include <allegro5/display.h>

namespace hen
{
	namespace ui
	{
		class Display
		{
		public:
			Display();
			Display(const Display&) = delete;
			Display(Display&&) = delete;
			~Display();

			Display& operator=(const Display&) = delete;
			Display& operator=(Display&&) = delete;

			void create(int width, int height, bool fullscreen);

			int getWidth() const;
			int getHeight() const;
			inline ALLEGRO_DISPLAY* getHandle() const { return m_handle; }

		private:
			ALLEGRO_DISPLAY* m_handle = nullptr;
		};
	}
}