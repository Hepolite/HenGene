
#include "hen/render/texture/Texture2DArray.h"

#include "hen/render/opengl/OpenGL.h"

#include <allegro5/allegro.h>

hen::texture::Texture2DArray::Texture2DArray(){}
hen::texture::Texture2DArray::~Texture2DArray()
{
	clear();
}

unsigned int hen::texture::Texture2DArray::attach(const io::File& file)
{
	if (m_isBuilt)
		return 0;

	const auto& result = m_fileHandles.find(file.getPath());
	if (result != m_fileHandles.end())
		return result->second;

	const unsigned int index = attach(al_load_bitmap(file.getPath().c_str()));
	m_fileHandles.emplace(file.getPath(), index);
	return index;
}
unsigned int hen::texture::Texture2DArray::attach(ALLEGRO_BITMAP* bitmap)
{
	if (m_isBuilt || bitmap == nullptr)
		return 0;
	unsigned int index = m_bitmaps.size();

	if (m_width == 0 || m_height == 0)
	{
		m_width = al_get_bitmap_width(bitmap);
		m_height = al_get_bitmap_height(bitmap);
	}

	int width = al_get_bitmap_width(bitmap);
	int height = al_get_bitmap_height(bitmap);
	if (width != m_width || height != m_height)
	{
		for (int y = 0; y < height; y += m_height)
		for (int x = 0; x < width; x += m_width)
			m_bitmaps.emplace_back(al_create_sub_bitmap(bitmap, x, y, m_width, m_height));
		m_parentBitmaps.emplace_back(bitmap);
	}
	else
		m_bitmaps.emplace_back(bitmap);
	m_depth = m_bitmaps.size();
	return index;
}

bool hen::texture::Texture2DArray::build()
{
	if (m_isBuilt || m_width == 0 || m_height == 0 || m_depth == 0)
		return false;
	m_isBuilt = true;

	bind();
	// TODO: Generalize this into underlying class
	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, m_width, m_height, m_depth, 0, GL_RGBA, GL_UNSIGNED_INT, (void*)0);
	unsigned int index = 0;
	for (auto bitmap : m_bitmaps)
	{
		// Dark sorcery. Don't question it
		ALLEGRO_LOCKED_REGION *region = al_lock_bitmap(bitmap, al_get_bitmap_format(bitmap), ALLEGRO_LOCK_READONLY);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index++, m_width, m_height, 1, GL_BGRA, GL_UNSIGNED_BYTE, (uint8_t*)region->data + (m_height - 1) * region->pitch);
		al_unlock_bitmap(bitmap);
	}

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	unbind();
	clear();
	return false;
}

void hen::texture::Texture2DArray::clear()
{
	m_fileHandles.clear();
	for (auto bitmap : m_bitmaps)
		al_destroy_bitmap(bitmap);
	m_bitmaps.clear();
	for (auto bitmap : m_parentBitmaps)
		al_destroy_bitmap(bitmap);
	m_parentBitmaps.clear();
}

