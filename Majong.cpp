#include "Majong.h"

int& Field::f(int x, int y, int z)
{
    return field[y + 2][x + 2][z];
}

int& Field::f(Vector3i v)
{
    return f(v.x, v.y, v.z);
}

bool Field::isOpen(int x, int y, int z)
{
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (f(x + 2, y + i, z) > 0 && f(x - 2, y + j, z) > 0)
                return false;

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (f(x + i, y + j, z + 1) > 0)
                return false;

    return true;
}


Majong::Majong()
{
}

void Majong::shuffleRemainingCards()
{
    std::vector<Vector3i> remainingCards;

    for (int z = 0; z < 10; z++)
        for (int x = 30; x >= 0; x--)
            for (int y = 0; y < 18; y++)
                if (f(x, y, z) > 0)
                    remainingCards.push_back(Vector3i(x, y, z));

    std::random_shuffle(remainingCards.begin(), remainingCards.end());

    int i = 0;

    for (auto& card : remainingCards)
    {
        f(card.x, card.y, card.z) = i++ + 1;

        if (i > 8) break;
    }
}

void Majong::create_map()
{
    for (int k = 1;; k++)
    {
        std::vector<Vector3i> opens;
        for (int z = 0; z < 10; z++)
            for (int y = 0; y < 18; y++)
                for (int x = 0; x < 30; x++)
                    if (f(x, y, z) > 0 && isOpen(x, y, z)) opens.push_back(Vector3i(x, y, z));

        int n = opens.size();
        if (n < 2) break;
        int a = 0, b = 0;
        while (a == b) { a = rand() % n; b = rand() % n; }
        f(opens[a]) = -k;  if (k > 34) k++;
        f(opens[b]) = -k;
        k %= 42;
    }
}

void Majong::load_file()
{
    std::fstream myfile("imgs/Majong/map.txt");
    for (int y = 0; y < 18; y++)
        for (int x = 0; x < 30; x++)
        {
            char a;
            myfile >> a;
            int n = a - '0';
            for (int z = 0; z < n; z++)
                if (f(x - 1, y - 1, z))
                    f(x - 1, y, z) = f(x, y - 1, z) = 0;
                else f(x, y, z) = 1;
        }
}

void Majong::move_back(std::vector<Vector3i> &moves)
{
    int n = moves.size();
    if (n != 0)
    {
        f(moves[n - 1]) *= -1; moves.pop_back();
        f(moves[n - 2]) *= -1; moves.pop_back();
    }
}

void Majong::fill_map()
{
    for (int z = 0; z < 10; z++)
        for (int y = 0; y < 18; y++)
            for (int x = 0; x < 30; x++)
                f(x, y, z) *= -1;
}

void Majong::handleCardClick(Vector2i mousePosition, Vector3i& selectedCardPos, bool& isSelected, Vector3i& v1, Vector3i& v2, std::vector<Vector3i>& moves)
{
    for (int z = 0; z < 10; z++)
    {
        Vector2i pos = mousePosition - Vector2i(30, 0); // 30 - desk offset
        int x = (pos.x - z * offX) / stepX;
        int y = (pos.y + z * offY) / stepY;

        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (f(x - i, y - j, z) > 0 && isOpen(x - i, y - j, z))
                {
                    v1 = Vector3i(x - i, y - j, z);
                    if (isSelected && selectedCardPos == v1)
                        isSelected = false;
                    else
                        isSelected = true;

                    selectedCardPos = v1;
                }

        if (v1 == v2)
            continue;

        int a = f(v1), b = f(v2);
        if (a == b || (a > 34 && a < 39 && b>34 && b < 39) || (a >= 39 && b >= 39))
        {
            f(v1) *= -1; moves.push_back(v1);
            f(v2) *= -1; moves.push_back(v2);
        }
        v2 = v1;

    }
}

void Majong::run()
{
    srand(time(0));
    bool isSelected = false;
    Vector3i selectedCardPos;
    RenderWindow window(VideoMode(740, 570), "Mahjong Solitaire!");

   
    Sprite s, sBackground;
    s.setTexture(ResManager::GetTexture("imgs/Majong/tiles.png"));
    sBackground.setTexture(ResManager::GetTexture("imgs/Majong/background.png"));
    Vector3i v1, v2;
    std::vector<Vector3i> moves;
    sf::RectangleShape shuffleButton(sf::Vector2f(50.f, 50.f));

    ////load from file////
    load_file();

    ////create map//////
    create_map();

    fill_map();


    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();

            if (e.type == Event::MouseButtonReleased)
                if (e.key.code == Mouse::Right)
                {
                    move_back(moves);
                }

            if (e.type == Event::MouseButtonPressed)
                if (e.key.code == Mouse::Left) 
                {
                    if (shuffleButton.getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
                        shuffleRemainingCards();
                    handleCardClick(Mouse::getPosition(window), selectedCardPos, isSelected, v1, v2, moves);
                }
        }

        draw(window, sBackground, s, isSelected, selectedCardPos, shuffleButton);

        window.draw(shuffleButton);
        window.display();
    }
}

void Majong::draw(RenderWindow& window, Sprite& sBackground, Sprite& s, bool& isSelected, Vector3i& selectedCardPos, sf::RectangleShape& shuffleButton)
{
    window.clear();
    window.draw(sBackground);
    for (int z = 0; z < 10; z++)
        for (int x = 30; x >= 0; x--)
            for (int y = 0; y < 18; y++)
            {
                int k = f(x, y, z) - 1;
                if (k < 0) continue;
                s.setTextureRect(IntRect(k * w, 0, w, h));
                if (isOpen(x, y, z))
                    s.setTextureRect(IntRect(k * w, h, w, h));
                if (isSelected && selectedCardPos == Vector3i(x, y, z))
                    s.setColor(sf::Color(255, 255, 255, 128));
                else
                    s.setColor(sf::Color(255, 255, 255, 255));
                s.setPosition(x * stepX + z * offX, y * stepY - z * offY);
                s.move(30, 0);

                window.draw(s);
            }
    shuffleButton.setFillColor(sf::Color::Green);
    shuffleButton.setPosition(10.f, 10.f);
}


