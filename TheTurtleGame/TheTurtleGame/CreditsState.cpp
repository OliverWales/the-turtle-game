#include "CreditsState.hpp"

#include "Definitions.hpp"
#include "MapGenerator.hpp"
#include "MainMenuState.hpp"

CreditsState::CreditsState(GameDataRef data) : _data(data)
{
	_view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(_data->window.getSize().x / PIXEL_SIZE, _data->window.getSize().y / PIXEL_SIZE));

	if (!_creditsTexture.loadFromFile(CREDITS))
	{
		exit(EXIT_FAILURE);
	}

	if (!_buttonsTexture.loadFromFile(CREDITS_BUTTONS))
	{
		exit(EXIT_FAILURE);
	}

	// background
	_backgroundMap = MapGenerator::marchingSquares<15, 9>(CREDITS_MAP);
	_backgroundTiles = TileMap::TileMap(TILE_SET, sf::Vector2u(TILE_SIZE, TILE_SIZE), _backgroundMap, 15, 9);
	_backgroundTiles.setPosition(sf::Vector2f(-240, -135));

	// credits
	_credits.setTexture(_creditsTexture);
	_credits.setPosition(-132 / 2, -72);

	// back
	_back.setTexture(_buttonsTexture, sf::Vector2i(0, 0), sf::Vector2i(74, 28));
	_back.setPosition(sf::Vector2i(-74 / 2, 92));
}

void CreditsState::update(float dt)
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
			if (_back.isHovered(_data->window))
			{
				_data->machine.replaceState(StateRef(new MainMenuState(_data)));
			}
		}
	}

	_back.update(_data->window);
}

void CreditsState::stepAnimation()
{
}

void CreditsState::draw()
{
	_data->window.setView(_view);

	_data->window.clear(BACKGROUND_COLOUR);
	_data->window.draw(_backgroundTiles);

	_data->window.draw(_credits);
	_data->window.draw(_back);

	_data->window.display();
}
