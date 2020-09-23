#include <SFML/Graphics.hpp>
#include <iostream>

#include "Definitions.hpp"
#include "MapGenerator.hpp"
#include "TileMap.hpp"
#include "Turtle.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "The Turtle Game", sf::Style::Fullscreen);
    sf::Clock clock;

    sf::View uiView = sf::View(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x / PIXEL_SIZE, window.getSize().y / PIXEL_SIZE));
    sf::RectangleShape divider = sf::RectangleShape(sf::Vector2f(2, window.getSize().y / 4));
    divider.setPosition(sf::Vector2f(-1, -divider.getSize().y / 2));
    divider.setFillColor(sf::Color(0, 0, 0, 127));

    sf::View player1View;
    player1View.setSize(sf::Vector2f(window.getSize().x / (PIXEL_SIZE * 2), window.getSize().y / PIXEL_SIZE));
    player1View.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));

    sf::View player2View;
    player2View.setSize(sf::Vector2f(window.getSize().x / (PIXEL_SIZE * 2), window.getSize().y / PIXEL_SIZE));
    player2View.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

    Turtle turtle1 = Turtle("Turtle1.png", sf::Vector2f(150, 150), sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, player1View);
    Turtle turtle2 = Turtle("Turtle2.png", sf::Vector2f(250, 150), sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, player2View);

    int* map = MapGenerator::generate<64, 64>(0.5, 2);
    TileMap level = TileMap("TileSet.png", sf::Vector2u(32, 32), map, 64, 64);

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
        //std::cout << "FPS: " << 1000 / elapsedTime << std::endl;

        turtle1.tryMove(elapsedTime);
        turtle2.tryMove(elapsedTime);
        window.clear(sf::Color(80, 120, 180));

        window.setView(turtle1.View);
        window.draw(turtle1);
        window.draw(turtle2);
        window.draw(level);

        window.setView(turtle2.View);
        window.draw(turtle1);
        window.draw(turtle2);
        window.draw(level);

        window.setView(uiView);
        window.draw(divider);

        window.display();
    }

    return 0;
}