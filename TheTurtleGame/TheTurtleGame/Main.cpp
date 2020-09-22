#include <SFML/Graphics.hpp>
#include <iostream>

#include "Turtle.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "The Turtle Game", sf::Style::Fullscreen);
    int screenWidth = window.getSize().x / 4;
    int screenHeight = window.getSize().y / 4;

    sf::View view;
    view.setCenter(sf::Vector2f(screenWidth/2.0, screenHeight/2.0));
    view.setSize(sf::Vector2f(screenWidth, screenHeight));
    window.setView(view);

    sf::Clock clock;

    Turtle turtle1 = Turtle("TestTurtle.png", sf::Vector2f(0, 0), sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
    Turtle turtle2 = Turtle("TestTurtle.png", sf::Vector2f(50, 0), sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);

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

        double elapsedTime = clock.restart().asMilliseconds();
        turtle1.tryMove(elapsedTime);
        turtle2.tryMove(elapsedTime);

        window.clear(sf::Color(80, 120, 180));
        window.draw(turtle1);
        window.draw(turtle2);
        window.display();
    }

    return 0;
}