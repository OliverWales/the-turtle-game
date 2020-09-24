#pragma once

#include <SFML/Graphics.hpp>

class Keypad : public sf::Drawable, public sf::Transformable
{
public:
	Keypad() {};
	void setKeys(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right);
	void setTexture(sf::Texture texture, sf::Vector2i size, int xOffset);
	void setPosition(sf::Vector2f position);
	void update();
	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
	sf::Keyboard::Key _upKey;
	sf::Keyboard::Key _downKey;
	sf::Keyboard::Key _leftKey;
	sf::Keyboard::Key _rightKey;
	sf::Texture _texture;
	sf::Vector2i _size;
	int _xOffset;
	sf::Sprite _up;
	sf::Sprite _down;
	sf::Sprite _left;
	sf::Sprite _right;
};

