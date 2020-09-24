#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
	Button() {};
	void setTexture(sf::Texture& texture, sf::Vector2i uv, sf::Vector2i size);
	void setPosition(sf::Vector2i position);

	bool isHovered(sf::RenderWindow& window);

	void update(sf::RenderWindow& window);
	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
	sf::Sprite _button;
	sf::Texture _texture;

	// texture coords
	sf::IntRect _normal;
	sf::IntRect _hovered;
	sf::IntRect _pressed;

	void setNormal();
	void setHovered();
	void setPressed();
};