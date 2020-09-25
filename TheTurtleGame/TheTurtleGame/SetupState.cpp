#include "SetupState.hpp"

#include "Definitions.hpp"
#include "MainMenuState.hpp"
#include "MapGenerator.hpp"
#include "TileMap.hpp"
#include "MainMenuState.hpp"
#include "GameState.hpp"

#include <iostream>

SetupState::SetupState(GameDataRef data) : _data(data)
{
	_view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(_data->window.getSize().x / PIXEL_SIZE, _data->window.getSize().y / PIXEL_SIZE));

	if (!_buttonsTexture.loadFromFile(SETUP_BUTTONS))
	{
		exit(EXIT_FAILURE);
	}

	if (!_titlesTexture.loadFromFile(SETUP_TITLES))
	{
		exit(EXIT_FAILURE);
	}

	if (!_turtleSelectorTexture.loadFromFile(TURTLE_SELECTOR))
	{
		exit(EXIT_FAILURE);
	}

	if (!_keyboardTexture.loadFromFile(KEYBOARD_BUTTONS))
	{
		exit(EXIT_FAILURE);
	}

	// background
	_backgroundMap = MapGenerator::marchingSquares<15, 9>(SETUP_MAP);
	_backgroundTiles = TileMap::TileMap(TILE_SET, sf::Vector2u(TILE_SIZE, TILE_SIZE), _backgroundMap, 15, 9);
	_backgroundTiles.setPosition(sf::Vector2f(-240, -135));

	// back
	_back.setTexture(_buttonsTexture, sf::Vector2i(0, 0), sf::Vector2i(74, 28));
	_back.setPosition(sf::Vector2i(-74 / 2, -120));

	// player titles
	int p1x = -100;
	_p1Title.setTexture(_titlesTexture);
	_p1Title.setTextureRect(sf::IntRect(0, 0, 120, 26));
	_p1Title.setPosition(p1x - 60, -80);

	int p2x = 100;
	_p2Title.setTexture(_titlesTexture);
	_p2Title.setTextureRect(sf::IntRect(0, 26, 124, 26));
	_p2Title.setPosition(p2x - 60, -80);

	// turtle selectors
	_p1Turtle.setTexture(_titlesTexture);
	_p1Turtle.setTextureRect(sf::IntRect(0, 52, 32, 7));
	_p1Turtle.setPosition(p1x - 60, -45);

	_p1Left.setTexture(_buttonsTexture, sf::Vector2i(0, 28), sf::Vector2i(10, 14));
	_p1Left.setPosition(sf::Vector2i(p1x - 36, -20));
	_p1TurtleSelector.setTexture(_turtleSelectorTexture, sf::Vector2i(58, 34));
	_p1TurtleSelector.setPosition(sf::Vector2f(p1x - 29, -30));
	_p1TurtleSelector.setIndex(_data->player1Turtle); // remember selection
	_p1Right.setTexture(_buttonsTexture, sf::Vector2i(0, 42), sf::Vector2i(10, 14));
	_p1Right.setPosition(sf::Vector2i(p1x + 26, -20));

	_p2Turtle.setTexture(_titlesTexture);
	_p2Turtle.setTextureRect(sf::IntRect(0, 52, 32, 7));
	_p2Turtle.setPosition(p2x - 60, -45);

	_p2Left.setTexture(_buttonsTexture, sf::Vector2i(0, 28), sf::Vector2i(10, 14));
	_p2Left.setPosition(sf::Vector2i(p2x - 36, -20));
	_p2TurtleSelector.setTexture(_turtleSelectorTexture, sf::Vector2i(58, 34));
	_p2TurtleSelector.setPosition(sf::Vector2f(p2x - 29, -30));
	_p2TurtleSelector.setIndex(_data->player2Turtle); // remember selection
	_p2Right.setTexture(_buttonsTexture, sf::Vector2i(0, 42), sf::Vector2i(10, 14));
	_p2Right.setPosition(sf::Vector2i(p2x + 26, -20));

	// controls
	_p1Controls.setTexture(_titlesTexture);
	_p1Controls.setTextureRect(sf::IntRect(0, 59, 44, 7));
	_p1Controls.setPosition(p1x - 60, 15);
	_p1Keys.setTexture(_keyboardTexture, sf::Vector2i(20, 19), 40);
	_p1Keys.setKeys(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
	_p1Keys.setPosition(sf::Vector2f(p1x - 31, 31));

	_p2Controls.setTexture(_titlesTexture);
	_p2Controls.setTextureRect(sf::IntRect(0, 59, 44, 7));
	_p2Controls.setPosition(p2x - 60, 15);
	_p2Keys.setTexture(_keyboardTexture, sf::Vector2i(20, 19), 0);
	_p2Keys.setKeys(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
	_p2Keys.setPosition(sf::Vector2f(p2x - 31, 31));

	// start
	_start.setTexture(_buttonsTexture, sf::Vector2i(0, 56), sf::Vector2i(85, 28));
	_start.setPosition(sf::Vector2i(-85 / 2, 92));
}

void SetupState::update(float dt)
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			_data->window.close();
		}

		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			if (_start.isHovered(_data->window))
			{
				_data->player1Turtle = _p1TurtleSelector.getIndex();
				_data->player2Turtle = _p2TurtleSelector.getIndex();
				_data->machine.replaceState(StateRef(new GameState(_data)));
			}

			if (_p1Left.isHovered(_data->window))
			{
				_p1TurtleSelector.prevItem();
				if(_p1TurtleSelector.getIndex() == _p2TurtleSelector.getIndex())
					_p1TurtleSelector.prevItem(); 
			}

			if (_p1Right.isHovered(_data->window))
			{
				_p1TurtleSelector.nextItem();
				if (_p1TurtleSelector.getIndex() == _p2TurtleSelector.getIndex())
					_p1TurtleSelector.nextItem();
			}

			if (_p2Left.isHovered(_data->window))
			{
				_p2TurtleSelector.prevItem();
				if (_p1TurtleSelector.getIndex() == _p2TurtleSelector.getIndex())
					_p2TurtleSelector.prevItem();
			}

			if (_p2Right.isHovered(_data->window))
			{
				_p2TurtleSelector.nextItem();
				if (_p1TurtleSelector.getIndex() == _p2TurtleSelector.getIndex())
					_p2TurtleSelector.nextItem();
			}

			if (_back.isHovered(_data->window))
			{
				_data->player1Turtle = _p1TurtleSelector.getIndex();
				_data->player2Turtle = _p2TurtleSelector.getIndex();
				_data->machine.replaceState(StateRef(new MainMenuState(_data)));
			}
		}
	}

	_back.update(_data->window);
	_p1Left.update(_data->window);
	_p1Right.update(_data->window);
	_p1Keys.update();
	_p2Left.update(_data->window);
	_p2Right.update(_data->window);
	_p2Keys.update();
	_start.update(_data->window);
}

void SetupState::stepAnimation()
{
}

void SetupState::draw()
{
	_data->window.setView(_view);

	_data->window.clear(BACKGROUND_COLOUR);
	_data->window.draw(_backgroundTiles);

	_data->window.draw(_back);

	_data->window.draw(_p1Title);
	_data->window.draw(_p1Turtle);
	_data->window.draw(_p2Title);
	_data->window.draw(_p2Turtle);

	_data->window.draw(_p1Left);
	_data->window.draw(_p1TurtleSelector);
	_data->window.draw(_p1Right);
	_data->window.draw(_p2Left);
	_data->window.draw(_p2TurtleSelector);
	_data->window.draw(_p2Right);

	_data->window.draw(_p1Controls);
	_data->window.draw(_p1Keys);
	_data->window.draw(_p2Controls);
	_data->window.draw(_p2Keys);

	_data->window.draw(_start);

	_data->window.display();
}