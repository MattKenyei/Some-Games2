#pragma once
#include "Games.h"
#include <fstream>
class Field 
{
protected:
	int field[22][34][10] = { 0 };

public:
    Field() {}

    int& f(int x, int y, int z);

    int& f(Vector3i v);

	bool isOpen(int x, int y, int z);
};

class Majong : public Field, public Games
{
public:
	ResManager rm;
    int w = 48, h = 66;
    int stepX = w / 2 - 2, stepY = h / 2 - 2;
    float offX = 4.6, offY = 7.1;
	Majong();
	void shuffleRemainingCards();
	void create_map();
	void load_file();
	void move_back(std::vector<Vector3i> &moves);
	void fill_map();
	void handleCardClick(Vector2i mousePosition, Vector3i& selectedCardPos, bool& isSelected, Vector3i& v1, Vector3i& v2, std::vector<Vector3i>& moves);
	void run();
	void draw(RenderWindow& window, Sprite& sBackground, Sprite& s, bool& isSelected, Vector3i& selectedCardPos, sf::RectangleShape& shuffleButton);
	int field[50][50][50] = { 0 };
	

};

