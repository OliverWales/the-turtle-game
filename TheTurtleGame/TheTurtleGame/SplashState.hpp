#pragma once

#include "State.hpp"
#include "Game.hpp"

class SplashState : public State
{
public:
	SplashState(GameDataRef data);
	void update(float dt);
	void stepAnimation();
	void draw();

private:
	GameDataRef _data;
	sf::Texture _splashTexture;
	sf::Sprite _splash;
	sf::Clock _clock;
};

