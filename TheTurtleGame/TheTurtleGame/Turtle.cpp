#include "Turtle.hpp"
#include "Definitions.hpp"
#include "Maths.hpp"

void Turtle::setTexture(sf::Texture& texture)
{
    _texture = texture;
    _sprite.setTexture(texture);
}

void Turtle::setPosition(sf::Vector2f position)
{
    Position = position;
    _sprite.setPosition(Position);
}

void Turtle::setKeys(sf::Keyboard::Key upKey, sf::Keyboard::Key downKey, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey)
{
    _upKey = upKey;
    _downKey = downKey;
    _leftKey = leftKey;
    _rightKey = rightKey;
}

void Turtle::setView(sf::View view)
{
    View = view;
    _viewMinX = View.getSize().x / 2;
    _viewMinY = View.getSize().y / 2;
    _viewMaxX = LEVEL_WIDTH * TILE_SIZE - _viewMinX;
    _viewMaxY = LEVEL_HEIGHT * TILE_SIZE - _viewMinY;

    float centreX = clamp(Position.x + (_texture.getSize().x / 8.f), _viewMinX, _viewMaxX);
    float centreY = clamp(Position.y + (_texture.getSize().y / 8.f), _viewMinY, _viewMaxY);
    View.setCenter(sf::Vector2f(centreX, centreY));
}

void Turtle::tryMove(double elapsedTime)
{
    // update sprite position
    bool up = sf::Keyboard::isKeyPressed(_upKey);
    bool down = sf::Keyboard::isKeyPressed(_downKey);
    bool left = sf::Keyboard::isKeyPressed(_leftKey);
    bool right = sf::Keyboard::isKeyPressed(_rightKey);

    _moving = false;
    if (up)
    {
        Position.y -= _speed * elapsedTime;
        _moving = true;
    }
    else if (down)
    {
        Position.y += _speed * elapsedTime;
        _moving = true;
    }

    if (left)
    {
        Position.x -= _speed * elapsedTime;
        faceLeft();
        _moving = true;
    }
    else if (right)
    {
        Position.x += _speed * elapsedTime;
        faceRight();
        _moving = true;
    }
        
    _sprite.setPosition(Position);

    // update camera position
    float centreX = clamp(Position.x + (_texture.getSize().x / 8.f), _viewMinX, _viewMaxX);
    float centreY = clamp(Position.y + (_texture.getSize().y / 8.f), _viewMinY, _viewMaxY);
    double viewX = lerp(View.getCenter().x, centreX, 0.003 * elapsedTime);
    double viewY = lerp(View.getCenter().y, centreY, 0.003 * elapsedTime);
    View.setCenter(sf::Vector2f(viewX, viewY));
}

void Turtle::faceLeft()
{
    _facingLeft = true;
    setUVs();
}

void Turtle::faceRight()
{
    _facingLeft = false;
    setUVs();
}

void Turtle::stepAnimation()
{
    if (_moving)
    {
        // turtle anims have 4 frames
        if (_frame < 3)
            _frame++;
        else
            _frame = 0;
        setUVs();
    };
}

void Turtle::draw(sf::RenderTarget& window, sf::RenderStates states) const
{
    window.draw(_sprite);
}

void Turtle::setUVs()
{
    if (_facingLeft)
    {
        _sprite.setTextureRect(sf::IntRect((_frame + 1) * (_texture.getSize().x / 4), 0, -1 * (_texture.getSize().x / 4), _texture.getSize().y));
    }
    else
    {
        _sprite.setTextureRect(sf::IntRect(_frame * (_texture.getSize().x / 4), 0, _texture.getSize().x / 4, _texture.getSize().y));
    }
}
