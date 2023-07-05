#include "Arkanoid.h"
float dot(const Vector2f& a, const Vector2f& b) {
    return a.x * b.x + a.y * b.y;
}
Vector2f reflect(const Vector2f& v, const Vector2f& n) {
    return v - 2.0f * dot(v, n) * n;
}


void Arkanoid::handleEvents(RenderWindow& m_window)
{
    Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == Event::Closed) 
        {
            m_window.close();
        }
    }
}

void Arkanoid::update(float dt, Ball& m_ball, Paddle& m_paddle, vector<Block>& m_blocks)
{
    // Обновление мяча
    m_ball.update(dt);
    // Проверка столкновений мяча со стенами и блоками
    //Левая стена
    if (m_ball.getPosition().x < 15)
    {
        float radius = m_ball.getVelocity().x;
        m_ball.setVelocity(sf::Vector2f(abs(m_ball.getVelocity().x), -abs(m_ball.getVelocity().y)));
        m_ball.setPosition(m_ball.getPosition().x + 5, m_ball.getPosition().y);
    }
    // Отскок от правой стены
    else if (m_ball.getPosition().x > 520 - 15)
    {
        m_ball.setVelocity(sf::Vector2f(-std::abs(m_ball.getVelocity().x), m_ball.getVelocity().y));
        m_ball.setPosition(520 - 15, m_ball.getPosition().y);
    }
    if (m_ball.getPosition().y < 0)
        m_ball.setVelocity(Vector2f(-abs(m_ball.getVelocity().x), -abs(m_ball.getVelocity().y)));
    //if (m_ball.getPosition().y < 0 && m_ball.getPosition().x < 0)
    //    m_ball.setVelocity(Vector2f(-abs(m_ball.getVelocity().x), -abs(m_ball.getVelocity().y)));
    if (m_ball.checkCollision(m_paddle.getShape())) {
        float ballPosition = m_ball.getPosition().x;
        float paddlePosition = m_paddle.getShape().getPosition().x;
        float paddleWidth = m_paddle.getShape().getSize().x;
        float relativeIntersect = (paddlePosition + (paddleWidth / 2)) - ballPosition;

        // Вычисляем новый вектор скорости мяча
        Vector2f velocity = m_ball.getVelocity();
        float magnitude = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (relativeIntersect > 0) {
            // Столкновение с левой стороной ракетки
            velocity.x = -std::abs(velocity.x);
        }
        else {
            // Столкновение с правой стороной ракетки
            velocity.x = std::abs(velocity.x);
        }
        float bounceAngle = relativeIntersect / (paddleWidth / 2.0f) * (M_PI / 3.0f);
        Vector2f normal(-sin(bounceAngle), cos(bounceAngle));
        Vector2f newVelocity = reflect(velocity / magnitude, normal) * magnitude;

        // Устанавливаем новый вектор скорости мяча
        m_ball.setVelocity(newVelocity);
    }
    for (auto& block : m_blocks) {
        if (!block.isDestroyed() && m_ball.checkCollision(block.getShape())) {
            block.setDestroyed(true);
            Vector2f blockPos = block.getShape().getPosition();
            Vector2f ballPos = m_ball.getPosition();
            Vector2f ballVel = m_ball.getVelocity();
            if (ballPos.x + 6 <= blockPos.x || ballPos.x + 6 >= blockPos.x + block.getShape().getSize().x) {
                ballVel.x = -ballVel.x;
            }
            else {
                ballVel.y = -ballVel.y;
            }
            m_ball.setVelocity(ballVel);
        }
    }
    m_paddle.update(dt);
    if (m_ball.getPosition().y > 450 || m_ball.getPosition().x < -50)
    {
        m_gameOver = true;
    }
}

//void Arkanoid::draw(RenderWindow &m_window, Ball m_ball, Paddle m_paddle, vector<Block> m_blocks)
//{
//    m_window.clear();
//
//    // Отрисовка фона, мяча и ракетки
//    m_window.draw(m_backgroundSprite);
//    m_ball.draw(m_window);
//    m_paddle.draw(m_window);
//
//    // Отрисовка блоков
//    for (auto& block : m_blocks) {
//        block.draw(m_window);
//    }
//
//    m_window.display();
//}

Arkanoid::Arkanoid()
{
    
}

void Arkanoid::run()
{
    ResManager rm;
    Clock clock;
    RenderWindow m_window(VideoMode(520, 450), "Arkanoid!");
    Texture m_blockTexture;
    Ball m_ball;
    Texture m_ballTexture;
    Texture m_paddleTexture;
    m_paddleTexture.loadFromFile("imgs/Arkanoid/paddle.png");
    m_ballTexture.loadFromFile("imgs/Arkanoid/ball.png");
    Paddle m_paddle(m_paddleTexture, 300.0f, 440.0f);
    vector<Block> m_blocks;
    m_gameOver = false;
    // Загрузка текстур и настройка спрайтов
    m_backgroundSprite.setTexture(ResManager::GetTexture("imgs/Arkanoid/background.jpg"));

    m_ball = Ball(350.0f, 200.0f, 10.0f, 12.0f, 6.0f);
    m_ball.setShapeTexture(m_ballTexture);



    m_blockTexture.loadFromFile("imgs/Arkanoid/block01.png");
    int n = 0;
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            Block block(m_blockTexture, i * 43.0f, j * 20.0f);
            m_blocks.push_back(block);
            n++;
        }
    }
    while (m_window.isOpen() && !m_gameOver) {
        float dt = clock.restart().asSeconds();

        handleEvents(m_window);
        update(dt, m_ball, m_paddle, m_blocks);
        m_window.clear();
        m_window.draw(m_backgroundSprite);
        m_ball.draw(m_window);
        m_paddle.draw(m_window);
        for (auto& block : m_blocks)
        {
            block.draw(m_window);
        }
        m_window.display();
    }
}
Vector2f normalize(Vector2f v) {
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length != 0.0f) {
        return Vector2f(v.x / length, v.y / length);
    }
    else {
        return Vector2f(0.0f, 0.0f);
    }
}

// Функция для поворота вектора на заданный угол
Vector2f rotate(Vector2f v, float angle) {
    float cosAngle = std::cos(angle);
    float sinAngle = std::sin(angle);
    return Vector2f(v.x * cosAngle - v.y * sinAngle, v.x * sinAngle + v.y * cosAngle);
}

// Функция для вычисления длины вектора
float length(Vector2f v) {
    return std::sqrt(v.x * v.x + v.y * v.y);
}

Ball::Ball()
{

}

Ball::Ball(float x, float y, float dx, float dy, float radius)
{
    m_shape.setRadius(radius);
    m_shape.setPosition(x, y);
    m_velocity.x = dx;
    m_velocity.y = dy;
}

void Ball::update(float dt)
{
    m_shape.move(m_velocity * (dt * 15));
}

void Ball::setShapeTexture(Texture t)
{
    m_shape.setTexture(&t);
}

Vector2f Ball::getPosition()
{
    return m_shape.getPosition();
}

void Ball::setPosition(float x, float y)
{
    m_shape.setPosition(x, y);
}

void Ball::setVelocity(Vector2f velocity)
{
    m_velocity = velocity;
}

Vector2f Ball::getVelocity()
{
    return m_velocity;
}

void Ball::draw(RenderWindow& window) const
{
    window.draw(m_shape);
}

bool Ball::checkCollision(const RectangleShape& shape)
{
    FloatRect ballBounds = m_shape.getGlobalBounds();
    FloatRect shapeBounds = shape.getGlobalBounds();

    return ballBounds.intersects(shapeBounds);
}

void Ball::reset(Vector2f position)
{
    m_velocity = position;
}

Block::Block(const Texture& texture, float x, float y)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(x, y);
    m_destroyed = false;
}

void Block::draw(RenderWindow& window) const
{
    if (!m_destroyed)
    {
        window.draw(m_sprite);
    }
}

bool Block::isDestroyed() const
{
    return m_destroyed;
}

void Block::setDestroyed(bool destroyed)
{
    m_destroyed = destroyed;
}

RectangleShape Block::getShape() const
{
    RectangleShape shape(Vector2f(m_sprite.getTextureRect().width, m_sprite.getTextureRect().height));
    shape.setPosition(m_sprite.getPosition());
    return shape;
}

Paddle::Paddle(const Texture& texture, float x, float y)
{
    m_shape.setSize(Vector2f(texture.getSize()));
    m_shape.setTexture(&texture);
    m_shape.setPosition(x, y);
    m_speed = 350.0f;
}

void Paddle::update(float dt)
{
    if (Keyboard::isKeyPressed(Keyboard::Left))
    {
        m_shape.move(-m_speed * dt, 0);
    }
    else if (Keyboard::isKeyPressed(Keyboard::Right)) {
        m_shape.move(m_speed * dt, 0);
    }
}

void Paddle::draw(RenderWindow& window) const
{
    window.draw(m_shape);
}

const RectangleShape& Paddle::getShape() const
{
    return m_shape;
}

void Paddle::reset(Vector2f position, float speed)
{
    m_shape.setPosition(position);
    m_speed = speed;
}