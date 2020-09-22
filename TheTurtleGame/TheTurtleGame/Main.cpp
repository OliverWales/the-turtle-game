#include <SFML/Graphics.hpp>
#include <iostream>

#include "Turtle.hpp"

double inline lerp(double v0, double v1, double t) {
    return (1 - t) * v0 + t * v1;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "The Turtle Game", sf::Style::Fullscreen);
    int screenWidth = window.getSize().x / 4;
    int screenHeight = window.getSize().y / 4;

    sf::View view;
    view.setSize(sf::Vector2f(screenWidth, screenHeight));
    view.setCenter(sf::Vector2f(screenHeight / 2.0, screenHeight / 2.0));
    window.setView(view);

    sf::Clock clock;

    Turtle turtle1 = Turtle("TestTurtle.png", sf::Vector2f(0, 0), sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
    Turtle turtle2 = Turtle("TestTurtle.png", sf::Vector2f(50, 0), sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);

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

        double viewX = lerp(view.getCenter().x, turtle1.Position.x, 0.003 * elapsedTime);
        double viewY = lerp(view.getCenter().y, turtle1.Position.y, 0.003 * elapsedTime);
        view.setCenter(sf::Vector2f(viewX, viewY));
        window.setView(view);

        window.clear(sf::Color(80, 120, 180));
        window.draw(turtle1);
        window.draw(turtle2);
        window.display();
    }

    return 0;
}