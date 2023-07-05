#include "Space.h"
std::list<manager*> entities;

bool isCollide(manager* a, manager* b)
{
    return (b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y) < (a->R + b->R) * (a->R + b->R);
}
Space::Space()
{
}

void Space::run()
{
    list<asteroid*> asters;
    list<bullet*> bullets;

    srand(time(0));
    int life = 3;

    RenderWindow window(VideoMode(W, H), "Asteroids!");
    window.setFramerateLimit(60);

    Texture t1, t3, t4, t5, t6, t7;
    t1.loadFromFile("imgs/Space/spaceship.png");
    t4.loadFromFile("imgs/Space/rock.png");
    t5.loadFromFile("imgs/Space/fire_blue.png");
    asteroid as;
    bullet bu;
    player pl;
    t1.setSmooth(true);

    Sprite background;
    background.setTexture(ResManager::GetTexture("imgs/Space/background.jpg"));;

    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(t1, 40, 0, 40, 40, 1, 0);
    Animation sPlayer_go(t1, 40, 40, 40, 40, 1, 0);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
        
    manager en;
    as.spawn_asteroids(asters, sRock);
    player* p;
    pl.spawn_player(entities, sPlayer, p);
    bool pl_life = true;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed)
                if (event.key.code == Keyboard::Space)
                {
                    bullet* b;
                    bu.spawn_bullet(bullets, sBullet, b, p);
                }
        }

        pl.move(p);

       
        for (auto e : entities)
        {
            if (e->name == "explosion")
            {
                e->anim.update();
                if (e->anim.isEnd())
                    e->life = 0;
            }
        }

        /*if (rand() % 150 == 0)
        {
            asteroid* a = new asteroid();
            a->settings(sRock, 0, rand() % H, rand() % 360, 25);
            entities.push_back(a);
        }*/

       

        //for (auto a : en.entities)
        //    for (auto b : en.entities)
        //    {
        //            if (isCollide(a, b))
        //            {
        //                // Обработка столкновения
        //                if (a->name == "asteroid" && b->name == "bullet")
        //                    as.onCollision(b, a, en.entities);
        //                if (a->name == "player" && b->name == "asteroid")
        //                {
        //                    pl.onCollision(b, a, en.entities);
        //                    p->life = false;
        //                }
        //                
        //            }
        //    }
       
        p->update();
        for (auto i = asters.begin(); i != asters.end();)
        {
            asteroid* ae = *i;
            ae->update();
            if (ae->life == false)
                i = asters.erase(i);
            else
                i++;
        }
        for (auto i = bullets.begin(); i != bullets.end();)
        {
            bullet* bt = *i;
            bt->update();
            if (bt->life == false)
                i = bullets.erase(i);
            else
                i++;
        }
        for (auto a : asters)
        {
            for (auto b : bullets)
            {
                if (isCollide(a, b))
                    as.onColl(b, a, asters, entities);
            }
            if (isCollide(a, p))
                p->onColl(a, p, entities);
        }
       

       
        if (pl_life)
            if (p->thrust)  
                p->anim = sPlayer_go;
            else
                p->anim = sPlayer;
        if (pl_life == false && life > 0)
        {
            life--;
            pl.spawn_player(entities, sPlayer, p);
            pl_life = true;
        }
        if (life == 0)
            window.close();
        //draw
        window.clear(); 
        window.draw(background);
        for (auto i : entities)
            i->draw(window);
        for (auto i : asters)
            i->draw(window);
        for (auto i : bullets)
            i->draw(window);
        window.display();
    }
}

Animation::Animation(Texture& t, int x, int y, int w, int h, int count, float Speed)
{
    Frame = 0;
    speed = Speed;

    for (int i = 0; i < count; i++)
        frames.push_back(IntRect(x + i * w, y, w, h));

    sprite.setTexture(t);
    sprite.setOrigin(w / 2, h / 2);
    sprite.setTextureRect(frames[0]);
}
void Animation::update()
{
    Frame += speed;
    int n = frames.size();
    if (Frame >= n) Frame -= n;
    if (n > 0) sprite.setTextureRect(frames[int(Frame)]);
}
bool Animation::isEnd()
{
    return Frame + speed >= frames.size();
}




asteroid::asteroid()
{
    dx = rand() % 8 - 4;
    dy = rand() % 8 - 4;
    name = "asteroid";
}

void asteroid::update()
{
    x += dx;
    y += dy;

    if (x > W) x = 0;  if (x < 0) x = W;
    if (y > H) y = 0;  if (y < 0) y = H;
}

void asteroid::die(asteroid*& en)
{
    en->life = false;
}

void asteroid::onColl(bullet*& other, asteroid*& him, list<asteroid*>& as, list<manager*>& entities)
{
    asteroid e;
    t3.loadFromFile("imgs/Space/explosions/type_C.png");
    t6.loadFromFile("imgs/Space/rock_small.png");
    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);

    if (other->name == "bullet")
    {
        e.die(him);
        other->die(other);
        e.explosion(entities, him, sExplosion);
        // Создать меньшие астероиды
        for (int i = 0; i < 2; i++)
        {
            //if (R == 15) continue; // Не создавать малые астероиды, если текущий астероид уже маленький

            asteroid* e = new asteroid();
            e->settings(sRock_small, e->x, e->y, rand() % 360, 15);
            as.push_back(e);
        }
    }
}

bullet::bullet()
{
    name = "bullet";
}

void bullet::spawn_bullet(std::list<bullet*>& bullets, Animation sBullet, bullet*& b, player* p)
{
    b = new bullet();
    b->settings(sBullet, p->x, p->y, p->angle, 10);
    bullets.push_back(b);
}



void bullet::die(bullet*& en)
{
    en->life = false;
}

void bullet::onCollision(manager*& other, manager*& him, std::list<manager*>& entities)
{
    t3.loadFromFile("imgs/Space/explosions/type_C.png");
    t6.loadFromFile("imgs/Space/rock_small.png");
    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);

    if (other->name == "asteroid")
    {
        // Создать взрыв
        manager* e = new manager();
        e->settings(sExplosion, other->x, other->y);
        e->name = "explosion";
        entities.push_back(e);

        // Уничтожить пулю и астероид
        life = false;
        // Создать меньшие астероиды
        for (int i = 0; i < 2; i++)
        {
            if (other->R == 15) continue;

            manager* e = new manager();
            e->settings(sRock_small, other->x, other->y, rand() % 360, 15);
            entities.push_back(e);
        }
    }
}

void bullet::update()
{
    dx = cos(angle * DEGTORAD) * 6;
    dy = sin(angle * DEGTORAD) * 6;
    x += dx;
    y += dy;

    if (x > W || x<0 || y>H || y < 0)
        life = 0;
}

player::player()
{
    name = "player";
}

void player::die(player*& p)
{
    p->life = false;
}

void player::die(manager*& en)
{
    en->life = false;
}

void player::spawn_player(list<manager*>& entities, Animation sPlayer, player*& p)
{
    p = new player();
    p->life = true;
    p->settings(sPlayer, W / 2, H / 2, 0, 20);
    entities.push_back(p);
}

void player::onColl(asteroid*& other, player*& him, std::list<manager*>& entities)
{
    Texture t7, t3;
    t3.loadFromFile("imgs/Space/explosions/type_A.png");
    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);

    
    if (other->name == "asteroid")
    {
        die(him);
        other->die(other);
        pexplosion(entities, him, sExplosion);
    }
}

void player::update()
{
    if (thrust)
    {
        dx += cos(angle * DEGTORAD) * 0.2;
        dy += sin(angle * DEGTORAD) * 0.2;
    }
    else
    {
        dx *= 0.99;
        dy *= 0.99;
    }

    int maxSpeed = 15;
    float speed = sqrt(dx * dx + dy * dy);
    if (speed > maxSpeed)
    {
        dx *= maxSpeed / speed;
        dy *= maxSpeed / speed;
    }

    x += dx;
    y += dy;

    if (x > W) x = 0; if (x < 0) x = W;
    if (y > H) y = 0; if (y < 0) y = H;
}

void player::move(player* &p)
{
    if (Keyboard::isKeyPressed(Keyboard::Right))
        p->angle += 3;
    if (Keyboard::isKeyPressed(Keyboard::Left))
        p->angle -= 3;
    if (Keyboard::isKeyPressed(Keyboard::Up))
        p->thrust = true;
    else p->thrust = false;
}

void player::respawn()
{
    x = W / 2;
    y = H / 2;
    dx = 0;
    dy = 0;
    R = 30;
    angle = 0;
    life = true;
    anim.sprite.setPosition(x, y);
}

void asteroid::spawn_asteroids(list<asteroid*>& asterts, Animation sRock)
{
    for (int i = 0; i < 15; i++)
    {
        asteroid* a = new asteroid();
        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
        asterts.push_back(a);
    }
}

void manager::settings(Animation& a, int X, int Y, float Angle, int radius)
{
    anim = a;
    x = X; y = Y;
    angle = Angle;
    R = radius;
}

void asteroid::explosion(list<manager*>& entities, asteroid*& a, Animation sExplosion)
{
    manager* e = new manager();
    e->settings(sExplosion, a->x, a->y);
    e->name = "explosion";
    entities.push_back(e);
}

void player::pexplosion(list<manager*>& entities, player*& p, Animation sExplosion)
{
    manager* e = new manager();
    e->settings(sExplosion, p->x, p->y);
    e->name = "explosion";
    entities.push_back(e);
}


void manager::draw(RenderWindow& win)
{
    anim.sprite.setPosition(x, y);
    anim.sprite.setRotation(angle + 90);
    win.draw(anim.sprite);

    CircleShape circle(R);
    circle.setFillColor(Color(255, 0, 0, 170));
    circle.setPosition(x, y);
    circle.setOrigin(R, R);
}
