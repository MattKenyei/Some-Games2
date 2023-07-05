//#include "Throne.h"
//
//Throne::Throne()
//{
//}
//
//Throne::Throne(Color c)
//{
//    x = rand() % 600;
//    y = rand() % 480;
//    color = c;
//    dir = rand() % 4;
//}
//
//void Throne::tick()
//{
//    if (dir == 0) 
//        y += 1;
//    if (dir == 1) 
//        x -= 1;
//    if (dir == 2) 
//        x += 1;
//    if (dir == 3) 
//        y -= 1;
//
//    if (x >= 600) x = 0;  if (x < 0) x = 600 - 1;
//    if (y >= 480) y = 0;  if (y < 0) y = 480 - 1;
//}
//
//int Throne::getSpeed()
//{
//    return speed;
//}
//
//Vector3f Throne::getColor()
//{
//    return Vector3f(color.r, color.g, color.b);
//}
//
//void Throne::run()
//{
//    ResManager rm;
//    bool Game = true;
//    srand(time(0));
//    RenderWindow window(VideoMode(600, 480), "The Throne Game!");
//    window.setFramerateLimit(60);
//
//    Sprite sBackground;
//    sBackground.setTexture(ResManager::GetTexture("imgs/Throne/background.png"));
//
//    Throne p1(Color::Red), p2(Color::Green);
//
//    Sprite sprite;
//    RenderTexture t;
//    t.create(600, 480);
//    t.setSmooth(true);
//    sprite.setTexture(t.getTexture());
//    t.clear();
//    t.draw(sBackground);
//
//    while (window.isOpen())
//    {
//        Event e;
//        while (window.pollEvent(e))
//        {
//            if (e.type == Event::Closed)
//                window.close();
//        }
//
//        if (Keyboard::isKeyPressed(Keyboard::A))
//            if (p1.dir != 2)
//                p1.dir = 1;
//        if (Keyboard::isKeyPressed(Keyboard::D))
//            if (p1.dir != 1)
//                p1.dir = 2;
//        if (Keyboard::isKeyPressed(Keyboard::W))
//            if (p1.dir != 0)
//                p1.dir = 3;
//        if (Keyboard::isKeyPressed(Keyboard::S))
//            if (p1.dir != 3)
//                p1.dir = 0;
//
//        if (Keyboard::isKeyPressed(Keyboard::Left))
//            if (p2.dir != 2)
//                p2.dir = 1;
//        if (Keyboard::isKeyPressed(Keyboard::Right))
//            if (p2.dir != 1)
//                p2.dir = 2;
//        if (Keyboard::isKeyPressed(Keyboard::Up))
//            if (p2.dir != 0)
//                p2.dir = 3;
//        if (Keyboard::isKeyPressed(Keyboard::Down))
//            if (p2.dir != 3)
//                p2.dir = 0;
//
//
//        for (int i = 0; i < p1.speed; i++)
//        {
//            p1.tick();
//            p2.tick();
//            if (p1.field[p1.x][p1.y] == 1)
//            {
//                cout << "Player 1 has crashed.\nPress Escape to back to menu or 5 to restart." << endl;
//                while (true)
//                {
//                    if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
//                    {
//                        window.~RenderWindow();
//                        Game = false;
//                        break;
//                    }
//                    if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
//                    {
//                        resetGame(p1, p2);
//                        window.clear();
//                        t.draw(sBackground);
//                        break;
//                    }
//                }
//
//            }
//            if (p1.field[p2.x][p2.y] == 1)
//            {
//                cout << "Player 2 has crashed. Press escape to exit." << endl;
//                while (true)
//                {
//                    if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
//                    {
//                        window.close();
//                        Game = false;
//                        break;
//                    }
//                    if (Keyboard::isKeyPressed(Keyboard::Key::Num5))
//                    {
//                        resetGame(p1, p2);
//                        window.clear();
//                        t.draw(sBackground);
//                        break;
//                    }
//                }
//            }
//            p1.field[p1.x][p1.y] = 1;
//            p1.field[p2.x][p2.y] = 1;
//
//            CircleShape c(3);
//            c.setPosition(p1.x, p1.y); c.setFillColor(p1.color);    t.draw(c);
//            c.setPosition(p2.x, p2.y); c.setFillColor(p2.color);    t.draw(c);
//            t.display();
//        }
//        if (Game)
//        {
//            ////// draw  ///////
//            window.clear();
//            window.draw(sprite);
//            window.display();
//        }
//        else
//            break;
//    }
//}
//
//void Throne::resetGame(Throne& p1, Throne& p2)
//{
//    for (int i = 0; i < 600; i++)
//        for (int j = 0; j < 480; j++)
//            p1.field[i][j] = 0;
//
//    int dir1 = rand() % 4;
//    int dir2 = rand() % 4;
//    p1.dir = dir1;
//    p2.dir = dir2;
//
//    p1.x = rand() % 600;
//    p1.y = rand() % 480;
//    p2.x = rand() % 600;
//    p2.y = rand() % 480;
//
//    p1.color = Color::Green;
//    p2.color = Color::Red;
//}
