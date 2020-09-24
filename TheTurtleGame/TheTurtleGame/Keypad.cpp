#include "Keypad.hpp"

void Keypad::setKeys(sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key left, sf::Keyboard::Key right)
{
	_upKey = up;
	_downKey = down;
	_leftKey = left;
	_rightKey = right;
}

void Keypad::setTexture(sf::Texture texture, sf::Vector2i size, int xOffset)
{
	_texture = texture;
	_size = size;
	_xOffset = xOffset;
	_up.setTexture(_texture);
	_up.setTextureRect(sf::IntRect(xOffset, 0, _size.x, _size.y));
	_down.setTexture(_texture);
	_down.setTextureRect(sf::IntRect(xOffset, _size.y, _size.x, _size.y));
	_left.setTexture(_texture);
	_left.setTextureRect(sf::IntRect(xOffset, 2 * _size.y, _size.x, _size.y));
	_right.setTexture(_texture);
	_right.setTextureRect(sf::IntRect(xOffset, 3 * _size.y, _size.x, _size.y));
}

void Keypad::setPosition(sf::Vector2f position)
{
	_up.setPosition(position + sf::Vector2f(_size.x + 1, 0));
	_down.setPosition(position + sf::Vector2f(_size.x + 1, _size.y + 1));
	_left.setPosition(position + sf::Vector2f(0, _size.y + 1));
	_right.setPosition(position + sf::Vector2f(2 * (_size.x + 1), _size.y + 1));
}

void Keypad::update()
{
	if(sf::Keyboard::isKeyPressed(_upKey))
		_up.setTextureRect(sf::IntRect(_xOffset + _size.x, 0, _size.x, _size.y));
	else
		_up.setTextureRect(sf::IntRect(_xOffset, 0, _size.x, _size.y));

	if (sf::Keyboard::isKeyPressed(_downKey))
		_down.setTextureRect(sf::IntRect(_xOffset + _size.x, _size.y, _size.x, _size.y));
	else
		_down.setTextureRect(sf::IntRect(_xOffset, _size.y, _size.x, _size.y));

	if (sf::Keyboard::isKeyPressed(_leftKey))
		_left.setTextureRect(sf::IntRect(_xOffset + _size.x, 2 * _size.y, _size.x, _size.y));
	else
		_left.setTextureRect(sf::IntRect(_xOffset, 2 * _size.y, _size.x, _size.y));

	if (sf::Keyboard::isKeyPressed(_rightKey))
		_right.setTextureRect(sf::IntRect(_xOffset + _size.x, 3 * _size.y, _size.x, _size.y));
	else
		_right.setTextureRect(sf::IntRect(_xOffset, 3 * _size.y, _size.x, _size.y));
}

void Keypad::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(_up);
	window.draw(_down);
	window.draw(_left);
	window.draw(_right);
}
