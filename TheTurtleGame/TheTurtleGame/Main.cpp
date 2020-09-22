#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "The Turtle Game", sf::Style::Fullscreen);
    int screenWidth = window.getSize().x / 4;
    int screenHeight = window.getSize().y / 4;

    sf::View view;
    view.setCenter(sf::Vector2f(screenWidth/2.0, screenHeight/2.0));
    view.setSize(sf::Vector2f(screenWidth, screenHeight));
    window.setView(view);

    sf::Texture turtleTexture;
    sf::Sprite turtleSprite;

    if (!turtleTexture.loadFromFile("TestTurtle.png"))
    {
        return 0;
    }
    turtleSprite.setTexture(turtleTexture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        window.clear(sf::Color(80, 120, 180));
        window.draw(turtleSprite);
        window.display();
    }

    return 0;
}