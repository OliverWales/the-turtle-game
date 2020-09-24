#pragma once

#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"

struct GameData
{
	sf::RenderWindow window;
	StateMachine machine;

	int player1Turtle;
	int player2Turtle;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
	public:
		Game(std::string title);

	private:
		GameDataRef _data = std::make_shared<GameData>();
		sf::Clock _clock;

		void run();
};

