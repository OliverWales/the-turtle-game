#pragma once

#include <SFML/Graphics.hpp>

class Turtle : public sf::Drawable
{
public:
	Turtle() {}
	void setTexture(sf::Texture& texture);
	void setPosition(sf::Vector2f position);
	void setKeys(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey);
	void setView(sf::View view);

	sf::View View;
	sf::Vector2f Position;

	void tryMove(double elapsedTime);
	void faceLeft();
	void faceRight();
	void stepAnimation();
	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Keyboard::Key _upKey;
	sf::Keyboard::Key _downKey;
	sf::Keyboard::Key _leftKey;
	sf::Keyboard::Key _rightKey;

	bool _moving = false;
	bool _facingLeft = false;
	int _frame = 1;

	float _viewMinX;
	float _viewMinY;
	float _viewMaxX;
	float _viewMaxY;

	double _speed = 0.15; // px per frame

	void setUVs();
};

