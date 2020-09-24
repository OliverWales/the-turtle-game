#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>

#include "Definitions.hpp"
#include "MapGenerator.hpp";
#include "TileMap.hpp";
#include "Button.hpp";
#include "MiniMap.hpp";
#include "Turtle.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "The Turtle Game", sf::Style::Fullscreen);
    sf::Clock clock;
    //srand(time(NULL));
    srand(0);

    int* map = MapGenerator::generate<LEVEL_WIDTH + 1, LEVEL_HEIGHT + 1>(0.47, 4);
    int* tiles = MapGenerator::marchingSquares<LEVEL_WIDTH, LEVEL_HEIGHT>(map);
    TileMap tileMap = TileMap::TileMap(TILE_SET, sf::Vector2u(TILE_SIZE, TILE_SIZE), tiles, LEVEL_WIDTH, LEVEL_HEIGHT);
    MiniMap<LEVEL_WIDTH + 1, LEVEL_HEIGHT + 1> miniMap = MiniMap<LEVEL_WIDTH + 1, LEVEL_HEIGHT + 1>(map);
    miniMap.setPosition(sf::Vector2f(-LEVEL_WIDTH / 2, (window.getSize().y / PIXEL_SIZE / 2) - LEVEL_HEIGHT - 1));
    sf::RectangleShape mmTurtle1 = sf::RectangleShape(sf::Vector2f(1, 1));
    mmTurtle1.setFillColor(sf::Color(132, 229, 12));
    sf::RectangleShape mmTurtle2 = sf::RectangleShape(sf::Vector2f(1, 1));
    mmTurtle2.setFillColor(sf::Color(255, 89, 194));


    sf::View uiView = sf::View(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x / PIXEL_SIZE, window.getSize().y / PIXEL_SIZE));
    sf::RectangleShape divider = sf::RectangleShape(sf::Vector2f(2, window.getSize().y / 4));
    divider.setPosition(sf::Vector2f(-1, -divider.getSize().y / 2));
    divider.setFillColor(sf::Color(0, 0, 0, 127));

    sf::Texture buttonsTexture;
    if (!buttonsTexture.loadFromFile("GameButtons.png"))
    {
        exit(EXIT_FAILURE);
    }
    Button home = Button();
    home.setTexture(buttonsTexture, sf::Vector2i(0, 0), sf::Vector2i(18, 18));
    home.setPosition(sf::Vector2i(2 - uiView.getSize().x / 2, 2 - uiView.getSize().y / 2));
    Button pause = Button();
    pause.setTexture(buttonsTexture, sf::Vector2i(0, 18), sf::Vector2i(18, 18));
    pause.setPosition(sf::Vector2i(22 - uiView.getSize().x / 2, 2 - uiView.getSize().y / 2));

    sf::View player1View;
    player1View.setSize(sf::Vector2f(window.getSize().x / (PIXEL_SIZE * 2), window.getSize().y / PIXEL_SIZE));
    player1View.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));

    sf::View player2View;
    player2View.setSize(sf::Vector2f(window.getSize().x / (PIXEL_SIZE * 2), window.getSize().y / PIXEL_SIZE));
    player2View.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

    Turtle turtle1 = Turtle("Turtle1.png", sf::Vector2f(150, 150), sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, player1View);
    Turtle turtle2 = Turtle("Turtle2.png", sf::Vector2f(250, 150), sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, player2View);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();

            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            {
                if (home.isHovered(window))
                {
                    std::cout << "Home" << std::endl;
                }

                if (pause.isHovered(window))
                {
                    std::cout << "Pause" << std::endl;
                }
            }
        }

        double elapsedTime = clock.restart().asMilliseconds();
        //std::cout << "FPS: " << 1000 / elapsedTime << std::endl;

        turtle1.tryMove(elapsedTime);
        turtle2.tryMove(elapsedTime);
        home.update(window);
        pause.update(window);

        mmTurtle1.setPosition(sf::Vector2f(miniMap.getPosition().x + (turtle1.Position.x + 37/2) / TILE_SIZE, miniMap.getPosition().y + (turtle1.Position.y + 20/2) / TILE_SIZE));
        mmTurtle2.setPosition(sf::Vector2f(miniMap.getPosition().x + (turtle2.Position.x + 37/2) / TILE_SIZE, miniMap.getPosition().y + (turtle2.Position.y + 20/2) / TILE_SIZE));
        window.clear(sf::Color(80, 120, 180));

        window.setView(turtle1.View);
        window.draw(turtle1);
        window.draw(turtle2);
        window.draw(tileMap);

        window.setView(turtle2.View);
        window.draw(turtle1);
        window.draw(turtle2);
        window.draw(tileMap);

        window.setView(uiView);
        window.draw(divider);
        window.draw(miniMap);
        window.draw(mmTurtle1);
        window.draw(mmTurtle2);
        window.draw(home);
        window.draw(pause);

        window.display();
    }

    return 0;
}