#include "AnimatedSprite.hpp"

void AnimatedSprite::setTexture(sf::Texture& texture, sf::Vector2i size, int frames)
{
	_texture = texture;
	_size = size;
	_sprite.setTexture(_texture);
	_sprite.setTextureRect(sf::IntRect(_currentFrame * _size.x, 0, _size.x, _size.y));
	_frames = frames;
}

void AnimatedSprite::setPosition(sf::Vector2f position)
{
	_sprite.setPosition(position);
}

void AnimatedSprite::stepAnimation()
{
	_currentFrame++;
	if (_currentFrame >= _frames) {
		_currentFrame = 0;
	}
	_sprite.setTextureRect(sf::IntRect(_currentFrame * _size.x, 0, _size.x, _size.y));
}

void AnimatedSprite::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(_sprite);
}
