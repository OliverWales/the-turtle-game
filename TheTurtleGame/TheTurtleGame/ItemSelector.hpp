#pragma once
#include <SFML/Graphics.hpp>

template<int N_ITEMS>
class ItemSelector : public sf::Drawable, public sf::Transformable
{
public:
	ItemSelector() {};

	void setTexture(sf::Texture& texture, sf::Vector2i size) {
		itemTextures = texture;

		for (int i = 0; i < N_ITEMS; i++)
		{
			frames[i] = { i * size.x, 0, size.x, size.y };
		}

		item.setTextureRect(frames[itemIndex]);
		item.setTexture(itemTextures);
	}


	void setIndex(int index) {
		itemIndex = index;
		apply();
	}

	void nextItem() {
		itemIndex++;
		if (itemIndex >= N_ITEMS) {
			itemIndex = 0;
		}
		apply();
	}

	void prevItem() {
		if (itemIndex <= 0) {
			itemIndex = N_ITEMS;
		}
		itemIndex--;
		apply();
	}

	int getIndex() {
		return itemIndex;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(item, states);
	}

private:
	sf::Sprite item;
	sf::Texture itemTextures;
	sf::IntRect frames[N_ITEMS];
	int itemIndex = 0;

	void apply() {
		item.setTextureRect(frames[itemIndex]);
		item.setTexture(itemTextures);
	}
};