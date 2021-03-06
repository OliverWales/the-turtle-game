#include "ArcadeGameState.hpp"

#include "Definitions.hpp"
#include "MapGenerator.hpp"
#include "MainMenuState.hpp"
#include "GameOverState.hpp"
#include <string>
#include <time.h>
#include <iostream>

ArcadeGameState::ArcadeGameState(GameDataRef data) : _data(data)
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

    // scores
    if (!_digitsTexture.loadFromFile(DIGITS))
    {
        exit(EXIT_FAILURE);
    }
    
    _p1Score.setTexture(_digitsTexture, sf::Vector2i(19, 26));
    _p1Score.setPosition(sf::Vector2f(sf::Vector2i(- _uiView.getSize().x / 4, 2 - _uiView.getSize().y / 2)));
    _p1Score.setValue(_p1Coins);

    _p2Score.setTexture(_digitsTexture, sf::Vector2i(19, 26));
    _p2Score.setPosition(sf::Vector2f(sf::Vector2i(_uiView.getSize().x / 4, 2 - _uiView.getSize().y / 2)));
    _p2Score.setValue(_p2Coins);

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

    // coins
    if (!_coinTexture.loadFromFile(COIN))
    {
        exit(EXIT_FAILURE);
    }

    while (_coins.size() < COIN_COUNT) {
        Coin coin = Coin();
        coin.setTexture(_coinTexture);
        replaceCoin(coin);
        _coins.push_back(coin);
    }
}

void ArcadeGameState::update(float dt)
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

    // collect coins
    for (Coin& coin : _coins)
    {
        if (coin.collides(sf::Vector2f(_p1Turtle.Position.x + _p1TurtleTexture.getSize().x / 8, _p1Turtle.Position.y + _p1TurtleTexture.getSize().y / 2)))
        {
            _p1Coins++;
            _p1Score.setValue(_p1Coins);
            replaceCoin(coin);
        } 
        else if (coin.collides(sf::Vector2f(_p2Turtle.Position.x + _p2TurtleTexture.getSize().x / 8, _p2Turtle.Position.y + _p2TurtleTexture.getSize().y / 2)))
        {
            _p2Coins++;
            _p2Score.setValue(_p2Coins);
            replaceCoin(coin);
        }
    }

    // check for winner
    if (_p1Coins >= 100) {
        // game over
        _data->winner = 1;
        _data->machine.replaceState(StateRef(new GameOverState(_data)));
    } else if (_p2Coins >= 100) {
        // game over
        _data->winner = 1;
        _data->machine.replaceState(StateRef(new GameOverState(_data)));
    }

    _home.update(_data->window);
    _pause.update(_data->window);
}

void ArcadeGameState::stepAnimation()
{
    _p1Turtle.stepAnimation();
    _p2Turtle.stepAnimation();
}

void ArcadeGameState::draw()
{
    _data->window.clear(BACKGROUND_COLOUR);

    // Player 1 view
    _data->window.setView(_p1Turtle.View);
    _data->window.draw(_p2Turtle);
    _data->window.draw(_p1Turtle);

    for (Coin& coin : _coins)
    {
        _data->window.draw(coin);
    }
    
    _data->window.draw(_tileMap);

    // Player 2 view
    _data->window.setView(_p2Turtle.View);
    _data->window.draw(_p1Turtle);
    _data->window.draw(_p2Turtle);

    for (Coin& coin : _coins)
    {
        _data->window.draw(coin);
    }
    
    _data->window.draw(_tileMap);

    // UI
    _data->window.setView(_uiView);
    _data->window.draw(_divider);
    _data->window.draw(_miniMap);
    _data->window.draw(_home);
    _data->window.draw(_p1Score);
    _data->window.draw(_p2Score);
    //_data->window.draw(_pause);

    _data->window.display();
}

void ArcadeGameState::replaceCoin(Coin &coin) {
    int x, y;

    do {
        x = rand() % LEVEL_WIDTH;
        y = rand() % LEVEL_HEIGHT;
    } while (_tiles[x + y * LEVEL_WIDTH] != 0);
    
    coin.setPosition(sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE));
}