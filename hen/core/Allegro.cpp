
#include "hen/core/Allegro.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <Log.h>

hen::core::Allegro::Allegro()
{
	LOG(plog::info) << "Initializing Allegro...";
	if (!al_init())
		LOG(plog::fatal) << "Failed to initialize Allegro";
	else
	{
		m_hasStartupErrors |= install(al_init_image_addon, "Initialized image addon", "Failed to initialize image addon");
		m_hasStartupErrors |= install(al_init_primitives_addon, "Initialized primitives addon", "Failed to initialize primitives addon");
		m_hasStartupErrors |= install(al_init_font_addon, "Initialized font addon");
		m_hasStartupErrors |= install(al_init_ttf_addon, "Initialized truetype font addon", "Failed to initialize truetype font addon");
		m_hasStartupErrors |= install(al_install_keyboard, "Initialized keyboard", "Failed to initialize keyboard");
		m_hasStartupErrors |= install(al_install_mouse, "Initialized mouse", "Failed to initialize mouse");

		m_isInitialized = true;
	}
}
hen::core::Allegro::~Allegro()
{
	LOG(plog::info) << "Shutting down Allegro";

	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_uninstall_system();
	al_uninstall_system();
}

bool hen::core::Allegro::install(const std::function<void()>& func, const std::string& succeeded) const
{
	func();
	LOG(plog::info) << succeeded;
	return false;
}
bool hen::core::Allegro::install(const std::function<bool()>& func, const std::string& succeeded, const std::string& failed) const
{
	if (func())
	{
		LOG(plog::info) << succeeded;
		return true;
	}
	else
	{
		LOG(plog::fatal) << failed;
		return false;
	}
}
