#include "TileMap.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

TileMap::TileMap(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
{
    // load the tileset texture
    if (!_tileset.loadFromFile(tileset))
        exit(EXIT_FAILURE);

    // resize the vertex array to fit the level size
    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(width * height * 4);
    int tileCount = 0;

    // populate the vertex array, with one quad per tile
    for (unsigned int i = 0; i < width; ++i)
    {
        for (unsigned int j = 0; j < height; ++j)
        {
            // get the current tile number
            int tileNumber = tiles[i + j * width];

            if (tileNumber != 0)
            {
                // find its position in the tileset texture
                int tu = tileNumber % (_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (_tileset.getSize().x / tileSize.x);

                // get a pointer to the current tile's quad
                sf::Vertex* quad = &_vertices[(tileCount) * 4];

                // define its 4 corners
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // define its 4 texture coordinates
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

                tileCount++;
            }
        }
    }
    _vertices.resize(tileCount * 4);
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &_tileset;

        // draw the vertex array
        target.draw(_vertices, states);
    }
}
