#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "TileMap.hpp"
#include "Turtle.hpp"
#include "Coin.hpp"
#include "Button.hpp"
#include "MiniMap.hpp"
#include "Number.hpp"
#include <vector>

class SurvivalGameState : public State
{
public:
	SurvivalGameState(GameDataRef data);
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
	sf::Texture _miniMapTexture;
	MiniMap<LEVEL_WIDTH + 1, LEVEL_HEIGHT + 1> _miniMap;

	sf::Texture _p1TurtleTexture;
	sf::Texture _p2TurtleTexture;
	Turtle _p1Turtle;
	Turtle _p2Turtle;

	sf::Texture _buttonsTexture;
	Button _home;
	Button _pause;

	sf::RectangleShape _divider;

	sf::Texture _fishTexture;
	std::vector<Coin> _fish;
	double _p1Health = 100;
	double _p2Health = 100;

	sf::Texture _healthBackTexture;
	sf::Sprite _p1HealthBack;
	sf::Sprite _p2HealthBack;
	sf::RectangleShape _p1HealthBar;
	sf::RectangleShape _p2HealthBar;

	void replaceCoin(Coin& coin);
};
