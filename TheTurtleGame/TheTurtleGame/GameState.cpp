#include "GameState.hpp"

#include "Definitions.hpp"
#include "MapGenerator.hpp"
#include "MainMenuState.hpp"
#include <string>

GameState::GameState(GameDataRef data) : _data(data)
{
    // generate level
    srand(0);
    _map = MapGenerator::generate<LEVEL_WIDTH + 1, LEVEL_HEIGHT + 1>(0.47, 4);
    _tiles = MapGenerator::marchingSquares<LEVEL_WIDTH, LEVEL_HEIGHT>(_map);
    _tileMap = TileMap::TileMap(TILE_SET, sf::Vector2u(TILE_SIZE, TILE_SIZE), _tiles, LEVEL_WIDTH, LEVEL_HEIGHT);

    // setup views
    _uiView = sf::View(sf::Vector2f(0, 0), sf::Vector2f(_data->window.getSize().x / PIXEL_SIZE, _data->window.getSize().y / PIXEL_SIZE));

    _p1View.setSize(sf::Vector2f(_data->window.getSize().x / (PIXEL_SIZE * 2), _data->window.getSize().y / PIXEL_SIZE));
    _p1View.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));

    _p2View.setSize(sf::Vector2f(_data->window.getSize().x / (PIXEL_SIZE * 2), _data->window.getSize().y / PIXEL_SIZE));
    _p2View.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));


    // buttons
    if (!_buttonsTexture.loadFromFile(GAME_BUTTONS))
    {
        exit(EXIT_FAILURE);
    }

    _home.setTexture(_buttonsTexture, sf::Vector2i(0, 0), sf::Vector2i(18, 18));
    _home.setPosition(sf::Vector2i(2 - _uiView.getSize().x / 2, 2 - _uiView.getSize().y / 2));
    _pause.setTexture(_buttonsTexture, sf::Vector2i(0, 18), sf::Vector2i(18, 18));
    _pause.setPosition(sf::Vector2i(22 - _uiView.getSize().x / 2, 2 - _uiView.getSize().y / 2));

    _divider = sf::RectangleShape(sf::Vector2f(2, _data->window.getSize().y / 4));
    _divider.setPosition(sf::Vector2f(-1, -_divider.getSize().y / 2));
    _divider.setFillColor(sf::Color(0, 0, 0, 127));

    // turtles
    if (!_p1TurtleTexture.loadFromFile("Turtle" + std::to_string(_data->player1Turtle) + ".png"))
    {
        exit(EXIT_FAILURE);
    }
    if (!_p2TurtleTexture.loadFromFile("Turtle" + std::to_string(_data->player2Turtle) + ".png"))
    {
        exit(EXIT_FAILURE);
    }

    _p1Turtle.setTexture(_p1TurtleTexture);
    _p1Turtle.setPosition(sf::Vector2f(92, 150));
    _p1Turtle.setKeys(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
    _p1Turtle.setView(_p1View);
    _p1Turtle.faceRight();

    _p2Turtle.setTexture(_p2TurtleTexture);
    _p2Turtle.setPosition(sf::Vector2f(TILE_SIZE * LEVEL_WIDTH - 150, 150));
    _p2Turtle.setKeys(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
    _p2Turtle.setView(_p2View);
    _p2Turtle.faceLeft();
}

void GameState::update(float dt)
{
    sf::Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _data->window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            _data->window.close();

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            if (_home.isHovered(_data->window))
            {
                _data->machine.replaceState(StateRef(new MainMenuState(_data)));
            }

            if (_pause.isHovered(_data->window))
            {
                std::cout << "Pause" << std::endl;
            }
        }
    }

    _p1Turtle.tryMove(dt);
    _p2Turtle.tryMove(dt);

    _home.update(_data->window);
    _pause.update(_data->window);
}

void GameState::stepAnimation()
{
    _p1Turtle.stepAnimation();
    _p2Turtle.stepAnimation();
}

void GameState::draw()
{
    _data->window.clear(BACKGROUND_COLOUR);

    _data->window.setView(_p1Turtle.View);
    _data->window.draw(_p2Turtle);
    _data->window.draw(_p1Turtle);
    _data->window.draw(_tileMap);
    //_data->window.draw(_tileMap);

    _data->window.setView(_p2Turtle.View);
    _data->window.draw(_p1Turtle);
    _data->window.draw(_p2Turtle);
    _data->window.draw(_tileMap);
    //_data->window.draw(_tileMap);

    _data->window.setView(_uiView);
    //_data->window.draw(divider);
    //_data->window.draw(miniMap);
    //_data->window.draw(mmTurtle1);
    //_data->window.draw(mmTurtle2);
    _data->window.draw(_home);
    _data->window.draw(_pause);
    _data->window.draw(_divider);

    _data->window.display();
}
