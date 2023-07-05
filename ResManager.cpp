#include "ResManager.h"
ResManager* ResManager::sInstance = nullptr;
ResManager::ResManager()
{
    sInstance = this;
}
Texture& ResManager::GetTexture(std::string const& filename)
{
	auto& texMap = sInstance->m_Textures;
	auto pairFound = texMap.find(filename);
	if (pairFound != texMap.end())
		return pairFound->second;
	else
	{
		auto& texture = texMap[filename];
		texture.loadFromFile(filename);
		return texture;
	}
}

Font& ResManager::GetFont(std::string const& filename)
{
	auto& fontMap = sInstance->m_Fonts;
	auto pairFound = fontMap.find(filename);

	if (pairFound != fontMap.end())
		return pairFound->second;
	else
	{
		auto& font = fontMap[filename];
		font.loadFromFile(filename);
		return font;
	}
}
