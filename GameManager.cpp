#include "GameManager.h"

GameManager::GameManager()
{
}

void GameManager::Run(bool &b)
{
    ResManager rm;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu");
    Font font;
    font.loadFromFile("WeblySleek UI Light.ttf");
    Sprite back;
    back.setTexture((ResManager::GetTexture("imgs/background.jpg")));
    sf::Text playButtonText;
    playButtonText.setFont(font);
    playButtonText.setString("Arkanoid");
    playButtonText.setCharacterSize(24);
    playButtonText.setPosition(350, 110);

    sf::Text magButtonText;
    magButtonText.setFont(font);
    magButtonText.setString("Majong");
    magButtonText.setCharacterSize(24);
    magButtonText.setPosition(350, 210);

    sf::Text spButtonText;
    spButtonText.setFont(font);
    spButtonText.setString("Space");
    spButtonText.setCharacterSize(24);
    spButtonText.setPosition(350, 310);

    sf::Text quitButtonText;
    quitButtonText.setFont(font);
    quitButtonText.setString("Quit");
    quitButtonText.setCharacterSize(24);
    quitButtonText.setPosition(350, 410);

    sf::RectangleShape MagButton(sf::Vector2f(200, 50));
    MagButton.setPosition(300, 200);
    MagButton.setFillColor(sf::Color::Blue);
    sf::RectangleShape SpButton(sf::Vector2f(200, 50));
    SpButton.setPosition(300, 300);
    SpButton.setFillColor(sf::Color::Blue);
    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setPosition(300, 100);
    playButton.setFillColor(sf::Color::Blue);
    RectangleShape quitButton(sf::Vector2f(200, 50));
    quitButton.setPosition(300, 400);
    quitButton.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {

                if (SpButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                    Space s;
                    s.run();
                }

                if (playButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                    Arkanoid a;
                    a.run();
                }
                if (MagButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    window.close();
                    Majong m;
                    m.run();
                }

                if (quitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    b = true;
                    window.close();
                }
            }
        }

        window.clear();
        window.draw(back);
        window.draw(playButton);
        window.draw(playButtonText);
        window.draw(MagButton);
        window.draw(magButtonText);
        window.draw(SpButton);
        window.draw(spButtonText);
        window.draw(quitButton);
        window.draw(quitButtonText);
        window.display();
    }
    window.close();

}

