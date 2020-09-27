#include "Coin.hpp"

void Coin::setTexture(sf::Texture& texture)
{
	_coin.setTexture(texture);
}

void Coin::setPosition(sf::Vector2f position)
{
	_coin.setPosition(position);
}

bool Coin::collides(sf::Vector2f position)
{
	return _coin.getGlobalBounds().contains(position);
}

void Coin::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(_coin);
}
