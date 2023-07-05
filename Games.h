#ifndef GAMES_H
#define GAMES_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <math.h>
#include "ResManager.h"

using namespace sf;
using namespace std;
class Games
{
private:
	float dyx;
public:
	virtual void run() = 0;
};
#endif
