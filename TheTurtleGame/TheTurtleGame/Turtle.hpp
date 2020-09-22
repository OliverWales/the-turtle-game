#pragma once

#include <SFML/Graphics.hpp>

class Turtle : public sf::Drawable
{
public:
	Turtle(std::string texture, sf::Vector2f position, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::View view);
	sf::View View;
	sf::Vector2f Position;

	void tryMove(double elapsedTime);
	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Keyboard::Key _upKey;
	sf::Keyboard::Key _downKey;
	sf::Keyboard::Key _leftKey;
	sf::Keyboard::Key _rightKey;

	double _speed = 0.1; // px per frame
};

