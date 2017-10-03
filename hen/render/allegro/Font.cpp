
#include "hen/render/allegro/Font.h"

#include "hen/io/XMLFile.h"

void hen::allegro::Font::onLoad(const io::File& file)
{
	onUnload();
	
	io::XMLFile xmlFile{ file };
	const auto& doc = xmlFile.open();
	const auto& font = doc.child("font");
	const std::string path = font.attribute("path").as_string();
	const int size = font.attribute("size").as_int(12);
	const int flags = font.attribute("flags").as_int();
	m_handle = al_load_font(path.c_str(), size, flags);
}
void hen::allegro::Font::onUnload()
{
	if (m_handle != nullptr)
		al_destroy_font(m_handle);
	m_handle = nullptr;
}
