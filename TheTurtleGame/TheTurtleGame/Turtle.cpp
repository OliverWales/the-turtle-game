#include "Turtle.hpp"

Turtle::Turtle(std::string texture, sf::Vector2f position, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey)
{
    if (!_texture.loadFromFile(texture))
    {
        exit(EXIT_FAILURE);
    }
    _sprite.setTexture(_texture);
    _sprite.setPosition(position);

    _upKey = upKey;
    _downKey = downKey;
    _leftKey = leftKey;
    _rightKey = rightKey;
    Position = _sprite.getPosition();
}

void Turtle::tryMove(double elapsedTime)
{
    bool up = sf::Keyboard::isKeyPressed(_upKey);
    bool down = sf::Keyboard::isKeyPressed(_downKey);
    bool left = sf::Keyboard::isKeyPressed(_leftKey);
    bool right = sf::Keyboard::isKeyPressed(_rightKey);

    if (up) {
        _sprite.setPosition(_sprite.getPosition() + sf::Vector2f(0, -_speed * elapsedTime));
    } else if (down) {
        _sprite.setPosition(_sprite.getPosition() + sf::Vector2f(0, _speed * elapsedTime));
    }

    if (left) {
        _sprite.setPosition(_sprite.getPosition() + sf::Vector2f(-_speed * elapsedTime, 0));
    } else if (right) {
        _sprite.setPosition(_sprite.getPosition() + sf::Vector2f(_speed * elapsedTime, 0));
    }

    Position = _sprite.getPosition();
}

void Turtle::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(_sprite);
}
