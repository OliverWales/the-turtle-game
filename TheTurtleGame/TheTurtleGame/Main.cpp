#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "The Turtle Game", sf::Style::Fullscreen);

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

        window.clear();
        // draw
        window.display();
    }

    return 0;
}