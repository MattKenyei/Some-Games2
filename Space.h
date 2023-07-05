#pragma once
#include "Games.h"
#include <list>
const int W = 1200;
const int H = 800;

class Space : public Games
{
private:
    ResManager rm;
public:
	Space();
	void run();
    
};

class Animation : public Space
{
private:
    float Frame, speed;
public:
    
    Sprite sprite;
    vector<IntRect> frames;

    Animation() {}

    Animation(Texture& t, int x, int y, int w, int h, int count, float Speed);

    void update();

    bool isEnd();

};

class manager
{
public:
    std::list<manager*> entities;
    manager() { life = 1; };
    manager* e;
    string name;
    bool life;
    Animation anim;
    float x, y, dx, dy, R, angle;
    void settings(Animation& a, int X, int Y, float Angle = 0, int radius = 1);

    void draw(RenderWindow& win);
    //std::list<manager*> entities;


};

class Entity : public Space
{
protected:
    Entity* e;
    double DEGTORAD = 0.017453;
public:
    virtual void update() = 0;
    virtual void die(manager*& en) = 0;
    virtual void onCollision(manager*& other, manager*& him, std::list<manager*>& entities)  = 0;
    virtual ~Entity() {};
};
class asteroid;
class player : public Entity, public manager
{
private:
    void respawn();
    void die(manager*& en);
    void onCollision(manager*& other, manager*& him, std::list<manager*>& entities) {};
public:
    bool thrust;

    player();
    void die(player*& p);
    void spawn_player(list<manager*>& entities, Animation sPlayer, player*& p);
    void onColl(asteroid*& other, player*& him, std::list<manager*>& entities);
    void update();
    void pexplosion(std::list<manager*>& entities, player*& p, Animation sExplosion);
    void move(player*& p);
};
class bullet : public Entity, public manager
{
private:
    Texture t3, t6;
    void die(manager*& en) {};
public:
    void update();
    bullet();
    void spawn_bullet(std::list<bullet*>& bullets, Animation sBullet, bullet*& b, player* p);
    void die(bullet*& en);
    void onCollision(manager*& other, manager*& him, std::list<manager*>& entities);

};

class asteroid : public Entity, public manager
{
private:
    void onCollision(manager*& other, manager*& him, std::list<manager*>& entities) {};
    void die(manager*& en) {};
public:
    Texture t3, t6;
    //float x, y, dx, dy, R, angle;
    asteroid();
    void update();
    void spawn_asteroids(list<asteroid*>& asterts, Animation sRock);
    void explosion(std::list<manager*>& entities, asteroid*& a, Animation sExplosion);
    void die(asteroid* &en);
    void onColl(bullet*& other, asteroid*& him, list<asteroid*>& as, list<manager*>& entities);
};