#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include "Arkanoid.h"
#include "Space.h"
#include "Majong.h"
#include "ResManager.h"

using namespace std;

class GameManager
{
public:
    GameManager();
    void Run(bool &f);
    virtual void run() {};
};
#endif