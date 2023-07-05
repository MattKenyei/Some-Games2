#include "GameManager.h"
int main()
{
	GameManager game;
	bool flag = false;
	while (true)
	{
		game.Run(flag);
		if (flag)
			break;
	}
	return 0;
}