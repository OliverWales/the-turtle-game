#include "SurvivalGameState.hpp"

#include "Definitions.hpp"
#include "MapGenerator.hpp"
#include "MainMenuState.hpp"
#include "GameOverState.hpp"
#include "Maths.hpp"
#include <string>
#include <time.h>
#include <iostream>

SurvivalGameState::SurvivalGameState(GameDataRef data) : _data(data)
{
    // generate level
    srand(0);
    _map = MapGenerator::generate<LEVEL_WIDTH + 1, LEVEL_HEIGHT + 1>(0.47, 4);
    _tiles = MapGenerator::marchingSquares<LEVEL_WIDTH, LEVEL_HEIGHT>(_map);
    _tileMap = TileMap::TileMap(TILE_SET, sf::Vector2u(TILE_SIZE, TILE_SIZE), _tiles, LEVEL_WIDTH, LEVEL_HEIGHT);

    srand(time(NULL));

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

    // health bars
    if (!_healthBackTexture.loadFromFile(HEALTH_BAR_BACK))
    {
        exit(EXIT_FAILURE);
    }

    _p1HealthBack.setTexture(_healthBackTexture);
    _p1HealthBack.setPosition(sf::Vector2f(-_uiView.getSize().x / 4 - 51, 7 - _uiView.getSize().y / 2));

    _p1HealthBar.setPosition(sf::Vector2f(-_uiView.getSize().x / 4 - 50, 8 - _uiView.getSize().y / 2));
    _p1HealthBar.setSize(sf::Vector2f(100, 6));

    _p2HealthBack.setTexture(_healthBackTexture);
    _p2HealthBack.setPosition(sf::Vector2f(_uiView.getSize().x / 4 - 51, 7 - _uiView.getSize().y / 2));

    _p2HealthBar.setPosition(sf::Vector2f(_uiView.getSize().x / 4 - 50, 8 - _uiView.getSize().y / 2));
    _p2HealthBar.setSize(sf::Vector2f(100, 6));

    // minimap
    _miniMap = MiniMap<LEVEL_WIDTH + 1, LEVEL_HEIGHT + 1>();
    _miniMap.setTexture(_miniMapTexture);
    _miniMap.setMap(_map);
    _miniMap.setPosition(sf::Vector2f(-LEVEL_WIDTH / 2, (_data->window.getSize().y / PIXEL_SIZE / 2) - LEVEL_HEIGHT - 1));
    _miniMap.setPlayerColours(*PLAYER_COLOURS[_data->player1Turtle], *PLAYER_COLOURS[_data->player2Turtle]);

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

    _miniMap.setPlayerPositions(_p1Turtle.Position, _p2Turtle.Position);

    // fish
    if (!_fishTexture.loadFromFile(FISH))
    {
        exit(EXIT_FAILURE);
    }

    while (_fish.size() < COIN_COUNT) {
        Coin fish = Coin();
        fish.setTexture(_fishTexture);
        replaceCoin(fish);
        _fish.push_back(fish);
    }
}

void SurvivalGameState::update(float dt)
{
    sf::Event event;
    while (_data->window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _data->window.close();

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                _data->window.close();
            }
            else if (event.key.code == sf::Keyboard::P)
            {
                sf::Texture screenshot;
                screenshot.create(_data->window.getSize().x, _data->window.getSize().y);
                screenshot.update(_data->window);

                std::string filename = "screenshot_" + std::to_string(time(NULL)) + ".png";
                if (screenshot.copyToImage().saveToFile(filename))
                {
                    std::cout << "Screenshot saved to " << filename << std::endl;
                }
            }
        }

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

    _p1Turtle.tryMove(dt, _tiles);
    _p2Turtle.tryMove(dt, _tiles);
    _miniMap.setPlayerPositions(_p1Turtle.Position, _p2Turtle.Position);

    // health
    _p1Health -= 0.003 * dt;
    _p2Health -= 0.003 * dt;

    for (Coin& fish : _fish)
    {
        if (fish.collides(sf::Vector2f(_p1Turtle.Position.x + _p1TurtleTexture.getSize().x / 8, _p1Turtle.Position.y + _p1TurtleTexture.getSize().y / 2)))
        {
            _p1Health += 5;
            if (_p1Health > 100) _p1Health = 100;
            replaceCoin(fish);
        }
        else if (fish.collides(sf::Vector2f(_p2Turtle.Position.x + _p2TurtleTexture.getSize().x / 8, _p2Turtle.Position.y + _p2TurtleTexture.getSize().y / 2)))
        {
            _p2Health += 5;
            if (_p2Health > 100) _p2Health = 100;
            replaceCoin(fish);
        }
    }

    // check for loser
    if (_p1Health < 0) {
        // game over
        _data->winner = 2;
        _data->machine.replaceState(StateRef(new GameOverState(_data)));
    } else if (_p2Health < 0) {
        // game over
        _data->winner = 1;
        _data->machine.replaceState(StateRef(new GameOverState(_data)));
    }

    // update healthbars
    _p1HealthBar.setSize(sf::Vector2f(_p1Health, 6));
    _p1HealthBar.setFillColor(RgbFromHsv(_p1Health / 300, 1.0, 1.0));
    _p2HealthBar.setSize(sf::Vector2f(_p2Health, 6));
    _p2HealthBar.setFillColor(RgbFromHsv(_p2Health / 300, 1.0, 1.0));

    _home.update(_data->window);
    _pause.update(_data->window);
}

void SurvivalGameState::stepAnimation()
{
    _p1Turtle.stepAnimation();
    _p2Turtle.stepAnimation();
}

void SurvivalGameState::draw()
{
    _data->window.clear(BACKGROUND_COLOUR);

    // Player 1 view
    _data->window.setView(_p1Turtle.View);
    _data->window.draw(_p2Turtle);
    _data->window.draw(_p1Turtle);

    for (Coin& fish : _fish)
    {
        _data->window.draw(fish);
    }

    _data->window.draw(_tileMap);

    // Player 2 view
    _data->window.setView(_p2Turtle.View);
    _data->window.draw(_p1Turtle);
    _data->window.draw(_p2Turtle);

    for (Coin& fish : _fish)
    {
        _data->window.draw(fish);
    }

    _data->window.draw(_tileMap);

    // UI
    _data->window.setView(_uiView);
    _data->window.draw(_divider);
    _data->window.draw(_miniMap);
    _data->window.draw(_home);

    _data->window.draw(_p1HealthBar);
    _data->window.draw(_p2HealthBar);

    _data->window.draw(_p1HealthBack);
    _data->window.draw(_p2HealthBack);
    //_data->window.draw(_pause);

    _data->window.display();
}

void SurvivalGameState::replaceCoin(Coin& coin) {
    int x, y;

    do {
        x = rand() % LEVEL_WIDTH;
        y = rand() % LEVEL_HEIGHT;
    } while (_tiles[x + y * LEVEL_WIDTH] != 0);

    coin.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
}