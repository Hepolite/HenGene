
#pragma once

#include "hen/asset/Ref.h"
#include "hen/render/allegro/Font.h"

#include <allegro5/allegro_font.h>
#include <glm/vec2.hpp>

#include <string>

namespace hen
{
	namespace render
	{
		class Text
		{
		public:
			enum Align { LEFT = 0, CENTER = 1, RIGHT = 2 };

			void setFont(const asset::Ref<allegro::Font>& font);
			void setFont(const ALLEGRO_FONT* font);
			void setText(const std::string& text);
			inline void setAlign(Align align) { m_align = align; }
			inline void setMaxWidth(float width) { m_fontSizeData.x = width; }
			inline void setLineHeight(float height) { m_fontSizeData.y = height; }

			inline std::string getText() const { return m_text; }
			inline Align getAlign() const { return m_align; }
			inline glm::vec2 getSize() const { return m_size; }
			inline float getMaxWidth() const { return m_fontSizeData.x; }
			inline float getLineHeight() const { return m_fontSizeData.y; }

			void render(const glm::vec2& pos) const;

		private:
			void recalculateSizeAndOffset();

			const ALLEGRO_FONT* m_font = nullptr;
			std::string m_text;
			Align m_align = Align::LEFT;

			glm::vec2 m_fontSizeData{ 1000000.0f, 0.0f };
			glm::vec2 m_size;
			glm::ivec2 m_offset;
		};
	}
}