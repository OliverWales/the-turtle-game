#include "SplashState.hpp"

#include "Definitions.hpp"
#include "MainMenuState.hpp"

SplashState::SplashState(GameDataRef data) : _data(data)
{
    if (!_splashTexture.loadFromFile(SPLASH_SCREEN))
    {
        exit(EXIT_FAILURE);
    }

    _splash.setTexture(_splashTexture);
}

void SplashState::update(float dt)
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			_data->window.close();
		}

		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
		{
			_data->window.close();
		}
	}

	if (_clock.getElapsedTime().asMilliseconds() > SPLASH_SCREEN_TIME)
	{
		// switch to the main menu state
		_data->machine.replaceState(StateRef(new MainMenuState(_data)));
	}
}

void SplashState::stepAnimation()
{
}

void SplashState::draw()
{
	this->_data->window.clear(sf::Color::Black);
	this->_data->window.draw(this->_splash);
	this->_data->window.display();
}