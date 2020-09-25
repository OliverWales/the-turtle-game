#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "ItemSelector.hpp"
#include "Keypad.hpp"
#include "TileMap.hpp"

class SetupState : public State
{
public:
	SetupState(GameDataRef data);
	void update(float dt);
	void stepAnimation();
	void draw();

private:
	GameDataRef _data;
	sf::View _view;

	sf::Texture _titlesTexture;
	sf::Sprite _p1Title;
	sf::Sprite _p1Turtle;
	sf::Sprite _p1Controls;
	sf::Sprite _p2Title;
	sf::Sprite _p2Turtle;
	sf::Sprite _p2Controls;

	sf::Texture _keyboardTexture;
	Keypad _p1Keys;
	Keypad _p2Keys;

	sf::Texture _buttonsTexture;
	Button _back;
	Button _p1Left;
	Button _p1Right;
	Button _p2Left;
	Button _p2Right;
	Button _start;

	sf::Texture _turtleSelectorTexture;
	ItemSelector<4> _p1TurtleSelector;
	ItemSelector<4> _p2TurtleSelector;

	int* _backgroundMap;
	TileMap _backgroundTiles;
};

