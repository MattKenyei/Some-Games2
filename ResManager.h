#ifndef RESMANAGER_H
#define RESMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <assert.h>
#include <map>
#include <memory>
using namespace sf;
using namespace std;
class ResManager
{
private:
	map<string, Texture> m_Textures;
	map<string, Font> m_Fonts;
	static ResManager* sInstance;
public:
	ResManager();
	static Texture& GetTexture(std::string const& filename);
	static Font& GetFont(std::string const& filename);
};
#endif