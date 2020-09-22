#include <SFML/Graphics.hpp>
#include <iostream>

#include "Turtle.hpp"

double inline lerp(double v0, double v1, double t) {
    return (1 - t) * v0 + t * v1;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "The Turtle Game", sf::Style::Fullscreen);
    int screenWidth = window.getSize().x / 8;
    int screenHeight = window.getSize().y / 4;

    sf::Clock clock;

    Turtle turtle1 = Turtle("TestTurtle.png", sf::Vector2f(0, 0), sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
    Turtle turtle2 = Turtle("TestTurtle.png", sf::Vector2f(50, 0), sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);

    sf::View player1View;
    player1View.setSize(sf::Vector2f(screenWidth, screenHeight));
    player1View.setCenter(turtle1.Position);
    player1View.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));

    sf::View player2View;
    player2View.setSize(sf::Vector2f(screenWidth, screenHeight));
    player2View.setCenter(turtle2.Position);
    player2View.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

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

        double player1ViewX = lerp(player1View.getCenter().x, turtle1.Position.x, 0.003 * elapsedTime);
        double player1ViewY = lerp(player1View.getCenter().y, turtle1.Position.y, 0.003 * elapsedTime);
        player1View.setCenter(sf::Vector2f(player1ViewX, player1ViewY));

        window.setView(player1View);
        window.draw(turtle1);
        window.draw(turtle2);

        double player2ViewX = lerp(player2View.getCenter().x, turtle2.Position.x, 0.003 * elapsedTime);
        double player2ViewY = lerp(player2View.getCenter().y, turtle2.Position.y, 0.003 * elapsedTime);
        player2View.setCenter(sf::Vector2f(player2ViewX, player2ViewY));

        window.setView(player2View);
        window.draw(turtle1);
        window.draw(turtle2);

        window.display();
    }

    return 0;
}