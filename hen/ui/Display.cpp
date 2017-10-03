
#include "hen/ui/Display.h"

hen::ui::Display::Display()
{}
hen::ui::Display::~Display()
{
	if (m_handle != nullptr)
		al_destroy_display(m_handle);
}

void hen::ui::Display::create(int width, int height, bool fullscreen)
{
	auto OPENGL = ALLEGRO_OPENGL | ALLEGRO_OPENGL_3_0;
	if (fullscreen)
		al_set_new_display_flags(OPENGL | ALLEGRO_FULLSCREEN_WINDOW);
	else
		al_set_new_display_flags(OPENGL | ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

	al_set_new_display_option(ALLEGRO_COLOR_SIZE, 32, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_DEPTH_SIZE, 24, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_STENCIL_SIZE, 8, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_AUX_BUFFERS, 0, ALLEGRO_REQUIRE);
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

	m_handle = al_create_display(width, height);
}

int hen::ui::Display::getWidth() const
{
	return m_handle == nullptr ? 0 : al_get_display_width(m_handle);
}
int hen::ui::Display::getHeight() const
{
	return m_handle == nullptr ? 0 : al_get_display_height(m_handle);
}
