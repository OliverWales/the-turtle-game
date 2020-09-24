#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "TileMap.hpp"
#include "Turtle.hpp"
#include "Button.hpp"

class GameState : public State
{
public:
	GameState(GameDataRef data);
	void update(float dt);
	void stepAnimation();
	void draw();

private:
	GameDataRef _data;
	sf::View _uiView;
	sf::View _p1View;
	sf::View _p2View;

	int* _map;
	int* _tiles;
	TileMap _tileMap;

	sf::Texture _p1TurtleTexture;
	sf::Texture _p2TurtleTexture;
	Turtle _p1Turtle;
	Turtle _p2Turtle;

	sf::Texture _buttonsTexture;
	Button _home;
	Button _pause;

	sf::RectangleShape _divider;
};
