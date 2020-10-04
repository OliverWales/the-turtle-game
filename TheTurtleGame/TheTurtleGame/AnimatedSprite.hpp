#pragma once

#include <SFML/Graphics.hpp>

class AnimatedSprite : public sf::Drawable, public sf::Transformable
{
public:
	AnimatedSprite() {};
	void setTexture(sf::Texture& texture, sf::Vector2i size, int frames);
	void setPosition(sf::Vector2f position);

	void stepAnimation();
	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2i _size;
	int _frames;
	int _currentFrame = 0;
};

