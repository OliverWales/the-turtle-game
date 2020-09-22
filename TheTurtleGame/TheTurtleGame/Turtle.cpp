#include "Turtle.hpp"
#include "Definitions.hpp"

Turtle::Turtle(std::string texture, sf::Vector2f position, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey, sf::View view)
{
    if (!_texture.loadFromFile(texture))
    {
        exit(EXIT_FAILURE);
    }

    Position = position;
    _sprite.setTexture(_texture);
    _sprite.setPosition(Position);

    _upKey = upKey;
    _downKey = downKey;
    _leftKey = leftKey;
    _rightKey = rightKey;
    Position = _sprite.getPosition();

    View = view;
    View.setCenter(Position);
}

double inline lerp(double v0, double v1, double t) {
    return (1 - t) * v0 + t * v1;
}

void Turtle::tryMove(double elapsedTime)
{
    bool up = sf::Keyboard::isKeyPressed(_upKey);
    bool down = sf::Keyboard::isKeyPressed(_downKey);
    bool left = sf::Keyboard::isKeyPressed(_leftKey);
    bool right = sf::Keyboard::isKeyPressed(_rightKey);

    if (up) {
        Position.y -= _speed * elapsedTime;
    } else if (down) {
        Position.y += _speed * elapsedTime;
    }

    if (left) {
        Position.x -= _speed * elapsedTime;
    } else if (right) {
        Position.x += _speed * elapsedTime;
    }
        
    _sprite.setPosition(Position);

    double viewX = lerp(View.getCenter().x, Position.x, 0.003 * elapsedTime);
    double viewY = lerp(View.getCenter().y, Position.y, 0.003 * elapsedTime);
    View.setCenter(sf::Vector2f(viewX, viewY));
}

void Turtle::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(_sprite);
}
