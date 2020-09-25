#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "TileMap.hpp"

class CreditsState : public State
{
public:
	CreditsState(GameDataRef data);
	void update(float dt);
	void stepAnimation();
	void draw();

private:
	GameDataRef _data;
	sf::View _view;

	sf::Texture _creditsTexture;
	sf::Sprite _credits;

	sf::Texture _buttonsTexture;
	Button _back;

	int* _backgroundMap;
	TileMap _backgroundTiles;
};

