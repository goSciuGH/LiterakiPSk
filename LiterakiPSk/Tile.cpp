#include "Tile.h"
#include "GameEngine.h"

Tile::Tile() : DrawableObject()
{
	myClasses.push_back("Tile");
}

Tile::Tile(sf::Vector2f pos, std::string textureName) : DrawableObject(pos, textureName)
{
	myClasses.push_back("Tile");
}

Tile::Tile(int l) : DrawableObject(l)
{
	myClasses.push_back("Tile");
}

Tile::Tile(int l, sf::Vector2f pos, std::string textureName) : DrawableObject(l, pos, textureName)
{
	myClasses.push_back("Tile");
}

void Tile::drawSelf(sf::RenderWindow& w) const
{
	for (const auto& spr : sprites)
	{
		w.draw(spr);
	}
	w.draw(letterVisual);
}
