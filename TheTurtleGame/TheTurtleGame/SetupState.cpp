#include "SetupState.hpp"

#include "Definitions.hpp"
#include "MainMenuState.hpp"
#include "MapGenerator.hpp"
#include "TileMap.hpp"
#include "MainMenuState.hpp"
#include "ArcadeGameState.hpp"
#include "SurvivalGameState.hpp"

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

	if (!_modeSelectorTexture.loadFromFile(MODE_SELECTOR))
	{
		exit(EXIT_FAILURE);
	}

	// background
	_backgroundMap = MapGenerator::marchingSquares<15, 9>(SETUP_MAP);
	_backgroundTiles = TileMap::TileMap(TILE_SET, sf::Vector2u(TILE_SIZE, TILE_SIZE), _backgroundMap, 15, 9);
	_backgroundTiles.setPosition(sf::Vector2f(-240, -135));

	// home
	_home.setTexture(_buttonsTexture, sf::Vector2i(0, 0), sf::Vector2i(18, 18));
	_home.setPosition(sf::Vector2i(2 - _view.getSize().x / 2, 2 - _view.getSize().y / 2));

	// player titles
	int p1x = -160;
	int y = -106;
	_p1Title.setTexture(_titlesTexture);
	_p1Title.setTextureRect(sf::IntRect(0, 0, 124, 26));
	_p1Title.setPosition(p1x, y);

	int p2x = 40;
	_p2Title.setTexture(_titlesTexture);
	_p2Title.setTextureRect(sf::IntRect(0, 26, 124, 26));
	_p2Title.setPosition(p2x, y);

	// turtle selectors
	_p1Turtle.setTexture(_titlesTexture);
	_p1Turtle.setTextureRect(sf::IntRect(0, 52, 32, 7));
	_p1Turtle.setPosition(p1x, y + 35);

	_p1Left.setTexture(_buttonsTexture, sf::Vector2i(0, 18), sf::Vector2i(10, 14));
	_p1Left.setPosition(sf::Vector2i(p1x + 24, y + 60));
	_p1TurtleSelector.setTexture(_turtleSelectorTexture, sf::Vector2i(58, 34));
	_p1TurtleSelector.setPosition(sf::Vector2f(p1x + 31, y + 50));
	_p1TurtleSelector.setIndex(_data->player1Turtle); // remember selection
	_p1Right.setTexture(_buttonsTexture, sf::Vector2i(0, 32), sf::Vector2i(10, 14));
	_p1Right.setPosition(sf::Vector2i(p1x + 86, y + 60));

	_p2Turtle.setTexture(_titlesTexture);
	_p2Turtle.setTextureRect(sf::IntRect(0, 52, 32, 7));
	_p2Turtle.setPosition(p2x , y + 35);

	_p2Left.setTexture(_buttonsTexture, sf::Vector2i(0, 18), sf::Vector2i(10, 14));
	_p2Left.setPosition(sf::Vector2i(p2x + 24, y + 60));
	_p2TurtleSelector.setTexture(_turtleSelectorTexture, sf::Vector2i(58, 34));
	_p2TurtleSelector.setPosition(sf::Vector2f(p2x + 31, y + 50));
	_p2TurtleSelector.setIndex(_data->player2Turtle); // remember selection
	_p2Right.setTexture(_buttonsTexture, sf::Vector2i(0, 32), sf::Vector2i(10, 14));
	_p2Right.setPosition(sf::Vector2i(p2x + 86, y + 60));

	// controls
	_p1Controls.setTexture(_titlesTexture);
	_p1Controls.setTextureRect(sf::IntRect(0, 59, 44, 7));
	_p1Controls.setPosition(p1x, y + 95);
	_p1Keys.setTexture(_keyboardTexture, sf::Vector2i(20, 19), 40);
	_p1Keys.setKeys(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D);
	_p1Keys.setPosition(sf::Vector2f(p1x + 29, y + 111));

	_p2Controls.setTexture(_titlesTexture);
	_p2Controls.setTextureRect(sf::IntRect(0, 59, 44, 7));
	_p2Controls.setPosition(p2x, y + 95);
	_p2Keys.setTexture(_keyboardTexture, sf::Vector2i(20, 19), 0);
	_p2Keys.setKeys(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right);
	_p2Keys.setPosition(sf::Vector2f(p2x + 29, y + 111));

	// mode
	_mode.setTexture(_titlesTexture);
	_mode.setTextureRect(sf::IntRect(0, 66, 25, 7));
	_mode.setPosition(p1x, y + 159);

	_modeLeft.setTexture(_buttonsTexture, sf::Vector2i(0, 18), sf::Vector2i(10, 14));
	_modeLeft.setPosition(sf::Vector2i(p1x, y + 179));
	_modeSelector.setTexture(_modeSelectorTexture, sf::Vector2i(133, 26));
	_modeSelector.setPosition(sf::Vector2f(p1x + 15, y + 173));
	_modeRight.setTexture(_buttonsTexture, sf::Vector2i(0, 32), sf::Vector2i(10, 14));
	_modeRight.setPosition(sf::Vector2i(p1x + 153, y + 179));

	_modeSelector.setIndex(1); // Arcade by default

	// start
	_start.setTexture(_buttonsTexture, sf::Vector2i(0, 46), sf::Vector2i(85, 28));
	_start.setPosition(sf::Vector2i(p2x + 18, y + 172));
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
			if (_home.isHovered(_data->window))
			{
				_data->player1Turtle = _p1TurtleSelector.getIndex();
				_data->player2Turtle = _p2TurtleSelector.getIndex();
				_data->machine.replaceState(StateRef(new MainMenuState(_data)));
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

			if (_modeLeft.isHovered(_data->window))
			{
				_modeSelector.prevItem();
			}

			if (_modeRight.isHovered(_data->window))
			{
				_modeSelector.nextItem();
			}

			if (_start.isHovered(_data->window))
			{
				_data->player1Turtle = _p1TurtleSelector.getIndex();
				_data->player2Turtle = _p2TurtleSelector.getIndex();
				_data->mode = _modeSelector.getIndex();

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
	_p1Left.update(_data->window);
	_p1Right.update(_data->window);
	_p1Keys.update();
	_p2Left.update(_data->window);
	_p2Right.update(_data->window);
	_p2Keys.update();
	_modeLeft.update(_data->window);
	_modeRight.update(_data->window);
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

	_data->window.draw(_home);

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

	_data->window.draw(_mode);
	_data->window.draw(_modeLeft);
	_data->window.draw(_modeSelector);
	_data->window.draw(_modeRight);

	_data->window.draw(_start);

	_data->window.display();
}