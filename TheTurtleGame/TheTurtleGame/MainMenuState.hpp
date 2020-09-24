#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "Button.hpp"

class MainMenuState : public State
{
public:
	MainMenuState(GameDataRef data);
	void update(float dt);
	void stepAnimation();
	void draw();

private:
	GameDataRef _data;
	sf::Texture _buttonsTexture;
	Button _play;
	Button _credits;
	Button _exit;
};

