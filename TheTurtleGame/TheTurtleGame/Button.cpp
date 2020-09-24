#include "Button.hpp"

void Button::setTexture(sf::Texture& texture, sf::Vector2i uv, sf::Vector2i size)
{
	this->_texture = texture;
	this->_button.setTexture(this->_texture);

	// set texture coords
	_normal = { uv.x + (0 * size.x), uv.y, size.x, size.y };
	_hovered = { uv.x + (1 * size.x), uv.y, size.x, size.y };
	_pressed = { uv.x + (2 * size.x), uv.y, size.x, size.y };

	_button.setTextureRect(_normal);
}

void Button::setPosition(sf::Vector2i position)
{
	_button.setPosition(sf::Vector2f(position));
}

bool Button::isHovered(sf::RenderWindow& window)
{
	return _button.getGlobalBounds().contains(sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
}

void Button::update(sf::RenderWindow& window)
{
	if (isHovered(window))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			setPressed();
		}
		else
		{
			setHovered();
		}
	}
	else
	{
		setNormal();
	}
}

void Button::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
	window.draw(_button);
}

void Button::setNormal()
{
	_button.setTextureRect(_normal);
}

void Button::setHovered()
{
	_button.setTextureRect(_hovered);
}

void Button::setPressed()
{
	_button.setTextureRect(_pressed);
}