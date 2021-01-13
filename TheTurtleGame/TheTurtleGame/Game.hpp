#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "StateMachine.hpp"

struct GameData
{
	sf::RenderWindow window;
	sf::Music music;
	StateMachine machine;

	int player1Turtle = 0;
	int player2Turtle = 1;
	int mode = 0;
	int winner = 0;
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

