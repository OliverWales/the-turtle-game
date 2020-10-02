#include "GameOverState.hpp"

#include "ArcadeGameState.hpp"

#include "Definitions.hpp"
#include "MainMenuState.hpp"
#include "ArcadeGameState.hpp"
#include "SurvivalGameState.hpp"

GameOverState::GameOverState(GameDataRef data) : _data(data)
{
    _view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(_data->window.getSize().x / PIXEL_SIZE, _data->window.getSize().y / PIXEL_SIZE));

    if (!_titleTexture.loadFromFile(GAME_OVER))
    {
        exit(EXIT_FAILURE);
    }

    int winningTurtle;
    if (_data->winner == 1) {
        winningTurtle = _data->player1Turtle;
    }
    else
    {
        winningTurtle = _data->player2Turtle;
    }

    if (!_winningTurtleTexture.loadFromFile("Turtle" + std::to_string(winningTurtle) + ".png"))
    {
        exit(EXIT_FAILURE);
    }

    if (!_crownTexture.loadFromFile(CROWN))
    {
        exit(EXIT_FAILURE);
    }

    if (!_buttonsTexture.loadFromFile(GAME_BUTTONS))
    {
        exit(EXIT_FAILURE);
    }

    _title.setTexture(_titleTexture);
    _title.setPosition(-77, -100);

    _turtle.setTexture(_winningTurtleTexture);
    _turtle.setTextureRect(sf::IntRect(38, 0, 38, 22));
    _turtle.setPosition(-19, 0);

    _crown.setTexture(_crownTexture);
    _crown.setPosition(9, -5);

    _home.setTexture(_buttonsTexture, sf::Vector2i(0, 0), sf::Vector2i(18, 18));
    _home.setPosition(sf::Vector2i(-29, 70));

    _retry.setTexture(_buttonsTexture, sf::Vector2i(0, 36), sf::Vector2i(18, 18));
    _retry.setPosition(sf::Vector2i(11, 70));
}

void GameOverState::update(float dt)
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

            if (_retry.isHovered(_data->window))
            {
                if (_data->mode == 0)
                {
                    // survival mode
                    _data->machine.replaceState(StateRef(new SurvivalGameState(_data)));
                }
                else
                {
                    // arcade mode
                    _data->machine.replaceState(StateRef(new ArcadeGameState(_data)));
                }
            }
        }
    }

    _home.update(_data->window);
    _retry.update(_data->window);
}

void GameOverState::stepAnimation()
{
}

void GameOverState::draw()
{
    _data->window.clear(BACKGROUND_COLOUR);

    _data->window.draw(_title);
    _data->window.draw(_turtle);
    _data->window.draw(_crown);
    _data->window.draw(_home);
    _data->window.draw(_retry);

    _data->window.display();
}
