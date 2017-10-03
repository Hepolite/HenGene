
#include "hen/render/allegro/Sprite.h"

#include "hen/io/XMLFile.h"

#include <allegro5/allegro.h>
#include <Log.h>

hen::allegro::Sprite::Sprite() {}
hen::allegro::Sprite::~Sprite()
{
	if (m_handle != nullptr)
		al_destroy_bitmap(m_handle);
}

void hen::allegro::Sprite::create(int width, int height)
{
	if (m_handle != nullptr)
		al_destroy_bitmap(m_handle);
	m_handle = al_create_bitmap(width, height);
	if (m_handle == nullptr)
		LOG(plog::warning) << "Failed to create bitmap of size " << width << ", " << height;
}

void hen::allegro::Sprite::onLoad(const io::File& file)
{
	io::XMLFile f{ file };
	const auto& doc = f.open();

	if (const auto& fileNode = doc.child("file"))
	{
		const std::string& path = fileNode.child_value();
		m_handle = al_load_bitmap(path.c_str());
		if (m_handle == nullptr)
			LOG(plog::warning) << "Failed to load bitmap " << path;
	}
	if (const auto frameNode = doc.child("frames"))
	{
		for (auto& child = frameNode.first_child(); child; child = child.next_sibling())
		{
			const std::string type = child.name();
			const std::string name = child.attribute("name").as_string();
			float x = child.attribute("x").as_float();
			float y = child.attribute("y").as_float();
			float w = child.attribute("w").as_float();
			float h = child.attribute("h").as_float();
			if (type == "single")
				m_frameNames.emplace(name, addFrame(x, y, w, h));
			else if (type == "row")
				m_frameNames.emplace(name, addFrameRow(x, y, w, h, child.attribute("sep").as_float(), child.attribute("count").as_int()));
			else if (type == "col")
				m_frameNames.emplace(name, addFrameCol(x, y, w, h, child.attribute("sep").as_float(), child.attribute("count").as_int()));
			else if (type == "grid")
				m_frameNames.emplace(name, addFrameGrid(x, y, w, h,
					child.attribute("sepx").as_float(), child.attribute("sepy").as_float(),
					child.attribute("countx").as_int(), child.attribute("county").as_int()
				));
		}
	}

}
void hen::allegro::Sprite::onUnload()
{
	if (m_handle != nullptr)
		al_destroy_bitmap(m_handle);
	m_handle = nullptr;
	m_frames.clear();
}

unsigned int hen::allegro::Sprite::addFrame(float x, float y, float width, float height)
{
	m_frames.emplace_back(x, y, width, height);
	return getFrameCount() - 1;
}
unsigned int hen::allegro::Sprite::addFrameRow(float x, float y, float width, float height, float sep, int count)
{
	return addFrameGrid(x, y, width, height, sep, 0.0f, count, 1);
}
unsigned int hen::allegro::Sprite::addFrameCol(float x, float y, float width, float height, float sep, int count)
{
	return addFrameGrid(x, y, width, height, 0.0f, sep, 1, count);
}
unsigned int hen::allegro::Sprite::addFrameGrid(float x, float y, float width, float height, float sepX, float sepY, int countX, int countY)
{
	const auto& index = getFrameCount();
	for (int j = 0; j < countY; ++j)
		for (int i = 0; i < countX; ++i)
			addFrame(x + i * (width + sepX), y + j * (height + sepY), width, height);
	return index;
}

hen::allegro::Sprite::Frame hen::allegro::Sprite::getFrame(unsigned int index) const
{
	return index >= getFrameCount() ? Frame{ 0.0f, 0.0f, 0.0f, 0.0f } : m_frames[index];
}
unsigned int hen::allegro::Sprite::getFrameIndex(const std::string& name) const
{
	const auto& result = m_frameNames.find(name);
	return result == m_frameNames.end() ? -1 : result->second;
}
void hen::allegro::Sprite::render(float x, float y, int flags) const
{
	if (m_handle == nullptr)
		return;
	al_draw_bitmap(m_handle, x, y, flags);
}
void hen::allegro::Sprite::render(unsigned int frame, float x, float y, int flags) const
{
	if (m_handle == nullptr || frame >= getFrameCount())
		return;
	const auto& f = m_frames[frame];
	al_draw_tinted_bitmap_region(m_handle, m_tint, f.m_x, f.m_y, f.m_w, f.m_h, x, y, flags);
}
void hen::allegro::Sprite::render(unsigned int frame, float x, float y, float angle, int flags) const
{
	if (m_handle == nullptr || frame >= getFrameCount())
		return;
	const auto& f = m_frames[frame];
	al_draw_tinted_scaled_rotated_bitmap_region(
		m_handle, f.m_x, f.m_y, f.m_w, f.m_h, m_tint,
		0.5f * f.m_w, 0.5f * f.m_h, x, y,
		1.0f, 1.0f, angle, flags
	);
}
void hen::allegro::Sprite::render(unsigned int frame, float x, float y, float width, float height, int flags) const
{
	render(frame, x, y, width, height, 0.0f, flags);
}
void hen::allegro::Sprite::render(unsigned int frame, float x, float y, float width, float height, float angle, int flags) const
{
	if (m_handle == nullptr || frame >= getFrameCount())
		return;
	const auto& f = m_frames[frame];
	al_draw_tinted_scaled_rotated_bitmap_region(
		m_handle, f.m_x, f.m_y, f.m_w, f.m_h, m_tint,
		0.0f, 0.0f, x, y,
		width / f.m_w, height / f.m_h, angle, flags
	);
}
