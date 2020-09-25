#include "Turtle.hpp"
#include "Definitions.hpp"
#include "Maths.hpp"
#include "MapGenerator.hpp"

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

void Turtle::tryMove(double dt, int* tiles)
{
    // update sprite position
    bool up = sf::Keyboard::isKeyPressed(_upKey);
    bool down = sf::Keyboard::isKeyPressed(_downKey);
    bool left = sf::Keyboard::isKeyPressed(_leftKey);
    bool right = sf::Keyboard::isKeyPressed(_rightKey);

    _moving = false;
    sf::Vector2f newPosition = Position;
    if (up)
    {
        newPosition.y -= _speed * dt;
        _moving = true;
    }
    else if (down)
    {
        newPosition.y += _speed * dt;
        _moving = true;
    }

    if (left)
    {
        newPosition.x -= _speed * dt;
        faceLeft();
        _moving = true;
    }
    else if (right)
    {
        newPosition.x += _speed * dt;
        faceRight();
        _moving = true;
    }
    
    if (_moving) {
        if (!collides(newPosition, tiles))
        {
            Position = newPosition;
            _sprite.setPosition(Position);
        }
        else
        {
            _moving = false;
        }
    }

    // update camera position
    float centreX = clamp(Position.x + (_texture.getSize().x / 8.f), _viewMinX, _viewMaxX);
    float centreY = clamp(Position.y + (_texture.getSize().y / 8.f), _viewMinY, _viewMaxY);
    double viewX = lerp(View.getCenter().x, centreX, 0.003 * dt);
    double viewY = lerp(View.getCenter().y, centreY, 0.003 * dt);
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

inline int getTile(sf::Vector2f position)
{
    int tileX = position.x / TILE_SIZE;
    int tileY = position.y / TILE_SIZE;
    return tileX + LEVEL_WIDTH * tileY;
}

inline sf::Vector2f getOffset(sf::Vector2f position)
{
    int tileX = position.x / TILE_SIZE;
    int tileY = position.y / TILE_SIZE;
    float x = position.x - (tileX * TILE_SIZE);
    float y = position.y - (tileY * TILE_SIZE);
    return sf::Vector2f(x, y);
}

bool Turtle::collides(sf::Vector2f position, int* tiles)
{
    int sizeX = _texture.getSize().x / 4;
    int sizeY = _texture.getSize().y;

    int topLeftTile = getTile(position);
    sf::Vector2f topLeftOffset = getOffset(position);

    sf::Vector2f topRight = sf::Vector2f(position.x + sizeX, position.y);
    int topRightTile = getTile(topRight);
    sf::Vector2f topRightOffset = getOffset(topRight);

    sf::Vector2f bottomLeft = sf::Vector2f(position.x, position.y + sizeY);
    int bottomLeftTile = getTile(bottomLeft);
    sf::Vector2f bottomLeftOffset = getOffset(bottomLeft);

    sf::Vector2f bottomRight = sf::Vector2f(position.x + sizeX, position.y + sizeY);
    int bottomRightTile = getTile(bottomRight);
    sf::Vector2f bottomRightOffset = getOffset(bottomRight);

    return MapGenerator::collides(tiles[topLeftTile], topLeftOffset)
        || MapGenerator::collides(tiles[topRightTile], topRightOffset)
        || MapGenerator::collides(tiles[bottomLeftTile], bottomLeftOffset)
        || MapGenerator::collides(tiles[bottomRightTile], bottomRightOffset);

}