
#pragma once

#include "hen/asset/Ref.h"
#include "hen/render/allegro/Font.h"
#include "hen/render/allegro/Sprite.h"

#include <unordered_map>

namespace hen
{
	namespace gui
	{
		class ComponentAsset
		{
		public:
			const asset::Ref<allegro::Font>& addFont(const std::string& font, const std::string& key = "");
			const asset::Ref<allegro::Sprite>& addSprite(const std::string& sprite, const std::string& key = "");
			const asset::Ref<allegro::Sprite>& createSprite(int width, int height, const std::string& key = "");

			std::string getPath(const std::string& key = "") const;
			const asset::Ref<allegro::Font>& getFont(const std::string& key = "") const;
			const asset::Ref<allegro::Sprite>& getSprite(const std::string& key = "") const;

		private:
			std::unordered_map<std::string, std::string> m_refPaths;
			std::unordered_map<std::string, asset::Ref<allegro::Font>> m_fonts;
			std::unordered_map<std::string, asset::Ref<allegro::Sprite>> m_sprites;
			asset::Ref<allegro::Font> m_fontRef;
			asset::Ref<allegro::Sprite> m_spriteRef;
		};
	}
}