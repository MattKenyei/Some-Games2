#ifndef ARKANOID_H
#define ARKANOID_H
#define _USE_MATH_DEFINES
#include "Games.h"
class Ball;
class Block;
class Paddle;
class Arkanoid :public Games
{
private:
	Sprite m_backgroundSprite;

	bool m_gameOver;
	void handleEvents(RenderWindow& m_window);
	void update(float dt, Ball& m_ball, Paddle& m_paddle, vector<Block>& m_blocks);

public:
	Arkanoid();
	virtual void draw(RenderWindow& m_window) {};
	void run();
	virtual ~Arkanoid() {};
};
class Ball : public Arkanoid {
private:
	CircleShape m_shape;
	Vector2f m_velocity;
public:
	Ball();
	Ball(float x, float y, float dx, float dy, float radius);
	void update(float dt);
	void setShapeTexture(Texture t);
	Vector2f getPosition();
	void setPosition(float x, float y);
	void setVelocity(Vector2f m_velocity);
	Vector2f getVelocity();
	void draw(RenderWindow& window) const;
	bool checkCollision(const RectangleShape& shape);
	void reset(Vector2f position);

};
class Block : public Arkanoid {
private:
	Sprite m_sprite;
	bool m_destroyed;
public:
	Block(const Texture& texture, float x, float y);
	void draw(RenderWindow& window) const;
	bool isDestroyed() const;
	void setDestroyed(bool destroyed);
	RectangleShape getShape() const;
};
class Paddle : public Arkanoid {
private:
	RectangleShape m_shape;
	float m_speed;
public:
	Paddle(const Texture& texture, float x, float y);
	void update(float dt);
	void draw(RenderWindow& window) const;
	const RectangleShape& getShape() const;
	void reset(Vector2f position, float speed);
};
#endif