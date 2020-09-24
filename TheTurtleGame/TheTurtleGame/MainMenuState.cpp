#include "MainMenuState.hpp"

#include "Definitions.hpp"
#include "MainMenuState.hpp"
#include "MapGenerator.hpp"
#include "TileMap.hpp"
#include "SetupState.hpp"

#include <iostream>

MainMenuState::MainMenuState(GameDataRef data) : _data(data)
{
	_uiView = sf::View(sf::Vector2f(0, 0), sf::Vector2f(_data->window.getSize().x / PIXEL_SIZE, _data->window.getSize().y / PIXEL_SIZE));

	if (!_titleTexture.loadFromFile(TITLE_BANNER))
	{
		exit(EXIT_FAILURE);
	}

	if (!_buttonsTexture.loadFromFile(MAIN_MENU_BUTTONS))
	{
		exit(EXIT_FAILURE);
	}

	_title.setTexture(_titleTexture);
	_title.setPosition(-282 / 2, -135);

	_play.setTexture(_buttonsTexture, sf::Vector2i(0, 0), sf::Vector2i(69, 28));
	_play.setPosition(sf::Vector2i(-69/2, -45));
	_credits.setTexture(_buttonsTexture, sf::Vector2i(0, 28), sf::Vector2i(112, 28));
	_credits.setPosition(sf::Vector2i(-112 / 2, -14));
	_exit.setTexture(_buttonsTexture, sf::Vector2i(0, 56), sf::Vector2i(60, 28));
	_exit.setPosition(sf::Vector2i(-60 / 2, 17));

	_backgroundMap = MapGenerator::marchingSquares<15, 9>(MAIN_MENU_MAP);
	_backgroundTiles = TileMap::TileMap(TILE_SET, sf::Vector2u(TILE_SIZE, TILE_SIZE), _backgroundMap, 15, 9);
	_backgroundTiles.setPosition(sf::Vector2f(-240, -135));
}

void MainMenuState::update(float dt)
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
			if (_play.isHovered(_data->window))
			{
				_data->machine.replaceState(StateRef(new SetupState(_data)));
			}

			if (_credits.isHovered(_data->window))
			{
				std::cout << "Credits" << std::endl;
			}

			if (_exit.isHovered(_data->window))
			{
				_data->window.close();
			}
		}
	}

	_play.update(_data->window);
	_credits.update(_data->window);
	_exit.update(_data->window);
}

void MainMenuState::stepAnimation()
{
}

void MainMenuState::draw()
{
	_data->window.clear(BACKGROUND_COLOUR);

	_data->window.setView(_uiView);
	_data->window.draw(_backgroundTiles);

	_data->window.draw(_title);
	_data->window.draw(_play);
	_data->window.draw(_credits);
	_data->window.draw(_exit);
	_data->window.display();
}