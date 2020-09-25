#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "Button.hpp"
#include "TileMap.hpp"

class MainMenuState : public State
{
public:
	MainMenuState(GameDataRef data);
	void update(float dt);
	void stepAnimation();
	void draw();

private:
	GameDataRef _data;

	sf::View _uiView;

	sf::Texture _titleTexture;
	sf::Sprite _title;

	sf::Texture _buttonsTexture;
	Button _play;
	Button _credits;
	Button _exit;

	int* _backgroundMap;
	TileMap _backgroundTiles;
};
