#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "Turtle.hpp"
#include "Button.hpp"

class GameOverState : public State
{
public:
	GameOverState(GameDataRef data);
	void update(float dt);
	void stepAnimation();
	void draw();

private:
	GameDataRef _data;
	sf::View _view;

	sf::Texture _titleTexture;
	sf::Sprite _title;

	sf::Texture _winningTurtleTexture;
	sf::Sprite _turtle;

	sf::Texture _crownTexture;
	sf::Sprite _crown;

	sf::Texture _buttonsTexture;
	Button _home;
	Button _retry;
};
