#pragma once

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"

template<int WIDTH, int HEIGHT>
class MiniMap : public sf::Drawable, public sf::Transformable
{
public:
    MiniMap() = default;

    void setTexture(sf::Texture& texture) {
        _texture = texture;
    }

    void setMap(int* map)
    {
        sf::Uint8* pixels = new sf::Uint8[WIDTH * HEIGHT * 4];

        for (int i = 0; i < WIDTH * HEIGHT; i++)
        {
            if (map[i] == 0) // water
            {
                pixels[4 * i] = BACKGROUND_COLOUR.r;
                pixels[4 * i + 1] = BACKGROUND_COLOUR.g;
                pixels[4 * i + 2] = BACKGROUND_COLOUR.b;
                pixels[4 * i + 3] = 255;
            }
            else
            {
                pixels[4 * i] = 255;
                pixels[4 * i + 1] = 223;
                pixels[4 * i + 2] = 149;
                pixels[4 * i + 3] = 255;
            }
        }

        _texture.create(WIDTH, HEIGHT);
        _texture.update(pixels);

        _sprite.setTexture(_texture);

        _background = sf::RectangleShape(sf::Vector2f(WIDTH + 2, HEIGHT + 2));
        _background.setFillColor(sf::Color(0, 0, 0, 127));
    }

    void setPlayerColours(sf::Color p1, sf::Color p2)
    {
        _player1.setFillColor(p1);
        _player2.setFillColor(p2);
    }

    void setPlayerPositions(sf::Vector2f p1, sf::Vector2f p2)
    {
        _player1.setPosition(sf::Vector2f(_sprite.getPosition().x + (p1.x + 37 / 2) / TILE_SIZE, _sprite.getPosition().y + (p1.y + 20 / 2) / TILE_SIZE));
        _player2.setPosition(sf::Vector2f(_sprite.getPosition().x + (p2.x + 37 / 2) / TILE_SIZE, _sprite.getPosition().y + (p2.y + 20 / 2) / TILE_SIZE));
    }

    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(_background, states);
        target.draw(_sprite, states);
        target.draw(_player1, states);
        target.draw(_player2, states);
    }

    void setPosition(sf::Vector2f position) {
        _background.setPosition(sf::Vector2f(position.x - 1, position.y - 1));
        _sprite.setPosition(position);
    }

    sf::Vector2f getPosition() {
        return _sprite.getPosition();
    }

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::RectangleShape _background;
    sf::RectangleShape _player1 = sf::RectangleShape(sf::Vector2f(1, 1));
    sf::RectangleShape _player2 = sf::RectangleShape(sf::Vector2f(1, 1));
};

