#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

class Coin : public sf::Drawable
{
public:
	Coin() {};
	void setTexture(sf::Texture& texture);
	void setPosition(sf::Vector2f position);
	bool collides(sf::Vector2f position);

	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
	sf::Texture _texture;
	sf::Sprite _coin;
};

