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

	sf::Texture _coinTexture;
	std::vector<Coin> _coins;
	int _p1Coins = 0;
	int _p2Coins = 0;

	sf::Texture _digitsTexture;
	Number _p1Score;
	Number _p2Score;

	void replaceCoin(Coin &coin);
};
