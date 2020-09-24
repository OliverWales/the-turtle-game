#include "Game.hpp"
#include "Definitions.hpp"
#include "StateMachine.hpp"
#include "SplashState.hpp"

#include "SetupState.hpp"

Game::Game(std::string title)
{
	_data->window.create(sf::VideoMode::getFullscreenModes()[0], title, sf::Style::Fullscreen);
	//_data->machine.addState(StateRef(new SplashState(_data)));
	_data->machine.addState(StateRef(new SetupState(_data)));
	run();
}

void Game::run() {
	float time = _clock.getElapsedTime().asMilliseconds();
	float lastTime = 0.f;
	float frameTime;

	while (_data->window.isOpen())
	{
		this->_data->machine.processStateChanges();
		time = _clock.getElapsedTime().asMilliseconds();
		frameTime = time - lastTime;
		lastTime = time;

		_data->machine.getCurrentState()->update(frameTime);

		if (time >= TICK_TIME)
		{
			_clock.restart();
			lastTime = 0.f;
			_data->machine.getCurrentState()->stepAnimation();
		}

		_data->machine.getCurrentState()->draw();
	}
}