#include "Number.hpp"

void Number::setTexture(sf::Texture& texture, sf::Vector2i size)
{
	_texture = texture;
	_digitSize = size;
	_digits.clear();
}

void Number::setPosition(sf::Vector2f position)
{
	_position = position;
}

void Number::setValue(int value)
{
	std::string number = std::to_string(value);
	_digits.clear();

	for (int i = 0; i < number.length(); i++)
	{
		sf::Sprite digit;
		digit.setTexture(_texture);
		digit.setTextureRect(sf::IntRect(_digitSize.x * (number[i] - '0'), 0, _digitSize.x, _digitSize.y));
		_digits.push_back(digit);
	}

	recalculatePosition();
}

void Number::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	for (auto& digit : _digits)
	{
		window.draw(digit);
	}
}

void Number::recalculatePosition()
{
	int length = _digits.size();
	sf::Vector2f left = sf::Vector2f(_position.x - (length / 2.f) * _digitSize.x, _position.y);

	for (auto& digit : _digits)
	{
		digit.setPosition(left);
		left.x += _digitSize.x;
	}
}
