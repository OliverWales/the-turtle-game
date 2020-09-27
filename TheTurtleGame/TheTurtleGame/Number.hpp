#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "ItemSelector.hpp"

class Number : public sf::Drawable
{
public:
	Number() {}
	void setTexture(sf::Texture& texture, sf::Vector2i size);
	void setPosition(sf::Vector2f position);

	void setValue(int value);

	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
	sf::Texture _texture;
	sf::Vector2i _digitSize;
	sf::Vector2f _position;
	std::vector<sf::Sprite> _digits;

	void recalculatePosition();
};

