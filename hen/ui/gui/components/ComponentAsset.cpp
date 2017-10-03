
#include "hen/ui/gui/components/ComponentAsset.h"

#include "hen/asset/AssetManager.h"
#include "hen/core/Core.h"

const hen::asset::Ref<hen::allegro::Font>& hen::gui::ComponentAsset::addFont(const std::string& font, const std::string& key)
{
	m_fonts[key] = hen::Core::getAssets().get<hen::allegro::Font>(font);
	m_refPaths[key] = font;
	return getFont(key);
}
const hen::asset::Ref<hen::allegro::Sprite>& hen::gui::ComponentAsset::addSprite(const std::string& sprite, const std::string& key)
{
	m_sprites[key] = hen::Core::getAssets().get<hen::allegro::Sprite>(sprite);
	m_refPaths[key] = sprite;
	return getSprite(key);
}
const hen::asset::Ref<hen::allegro::Sprite>& hen::gui::ComponentAsset::createSprite(int width, int height, const std::string& key)
{
	auto sprite = std::make_unique<allegro::Sprite>();
	sprite->create(width, height);
	m_sprites[key] = asset::Ref<allegro::Sprite>{ std::move(sprite) };
	return getSprite(key);
}

std::string hen::gui::ComponentAsset::getPath(const std::string& key) const
{
	const auto& result = m_refPaths.find(key);
	return result == m_refPaths.end() ? "" : result->second;
}

const hen::asset::Ref<hen::allegro::Font>& hen::gui::ComponentAsset::getFont(const std::string& key) const
{
	const auto& result = m_fonts.find(key);
	return result == m_fonts.end() ? m_fontRef : result->second;
}
const hen::asset::Ref<hen::allegro::Sprite>& hen::gui::ComponentAsset::getSprite(const std::string& key) const
{
	const auto& result = m_sprites.find(key);
	return result == m_sprites.end() ? m_spriteRef : result->second;
}


