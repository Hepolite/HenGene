
#include "hen/render/Text.h"

#include "hen/asset/AssetManager.h"
#include "hen/core/Core.h"
#include "hen/util/MathLib.h"
#include "hen/util/StringLib.h"

namespace
{
	glm::ivec2 textSize;
	glm::ivec2 textOffset;
	void reset()
	{
		textSize.x = textSize.y = textOffset.x = textOffset.y = 0;
	}
	bool callback(int number, const ALLEGRO_USTR* text, void* extra)
	{
		auto font = static_cast<const ALLEGRO_FONT*>(extra);
		if (font == nullptr)
			return false;

		if (number == 0)
		{
			int _;
			textSize.x = textSize.y = 0;
			al_get_ustr_dimensions(font, text, &textOffset.x, &textOffset.y, &_, &_);
		}

		textSize.x = hen::math::max(textSize.x, al_get_ustr_width(font, text));
		textSize.y = number + 1;
		return true;
	}
}

void hen::render::Text::setFont(const asset::Ref<allegro::Font>& font)
{
	setFont(font == nullptr ? nullptr : font->getHandle());
}
void hen::render::Text::setFont(const ALLEGRO_FONT* font)
{
	m_font = font;

	if (m_font != nullptr)
		setLineHeight(al_get_font_line_height(m_font));
}
void hen::render::Text::setText(const std::string& text)
{
	m_text = string::replace_all(text, "\\n", "\n");
	recalculateSizeAndOffset();
}

void hen::render::Text::recalculateSizeAndOffset()
{
	if (m_font == nullptr)
		return;

	reset();
	ALLEGRO_USTR* ustr = al_ustr_new(m_text.c_str());
	al_do_multiline_ustr(m_font, m_fontSizeData.x, ustr, &callback, (void*)m_font);
	al_ustr_free(ustr);

	m_size.x = textSize.x;
	m_size.y = textSize.y * m_fontSizeData.y - textOffset.y;
	m_offset = textOffset;
}

void hen::render::Text::render(const glm::vec2& pos) const
{
	const ALLEGRO_COLOR color{ 1.0f, 1.0f, 1.0f, 1.0f };

	if (m_font != nullptr)
		al_draw_multiline_text(
			m_font, color,
			pos.x - m_offset.x, pos.y - m_offset.y,
			m_fontSizeData.x, m_fontSizeData.y,
			ALLEGRO_ALIGN_INTEGER | m_align,
			m_text.c_str()
		);
}


