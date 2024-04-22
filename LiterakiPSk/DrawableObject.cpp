#include "DrawableObject.h"
#include "GameEngine.h"

DrawableObject::DrawableObject()
{
	myClasses.push_back("GameObject");
	myClasses.push_back("DrawableObject");
	layer = 0;
	pos = { 0.0f, 0.0f };
	objID = nextID++;
}

DrawableObject::DrawableObject(std::string textureName)
{
	myClasses.push_back("GameObject");
	myClasses.push_back("DrawableObject");
	layer = 0;

	pos = { 0.0f, 0.0f };

	sf::Sprite tempSprite(textures[textureName]);
	tempSprite.setPosition(pos);
	sprites.push_back(tempSprite);

	objID = nextID++;
}

DrawableObject::DrawableObject(sf::Vector2f pos)
{
	myClasses.push_back("GameObject");
	myClasses.push_back("DrawableObject");
	layer = 0;
	this->pos = pos;
	objID = nextID++;
}

DrawableObject::DrawableObject(sf::Vector2f pos, std::string textureName)
{
	myClasses.push_back("GameObject");
	myClasses.push_back("DrawableObject");
	layer = 0;
	this->pos = pos;

	sf::Sprite tempSprite(textures[textureName]);
	tempSprite.setPosition(pos);
	sprites.push_back(tempSprite);

	objID = nextID++;
}

DrawableObject::DrawableObject(int l)
{
	myClasses.push_back("GameObject");
	myClasses.push_back("DrawableObject");
	layer = l;
	pos = { 0.0f, 0.0f };
	objID = nextID++;
}

DrawableObject::DrawableObject(int l, std::string textureName)
{
	myClasses.push_back("GameObject");
	myClasses.push_back("DrawableObject");
	layer = l;
	pos = { 0.0f, 0.0f };

	sf::Sprite tempSprite(textures[textureName]);
	tempSprite.setPosition(pos);
	sprites.push_back(tempSprite);

	objID = nextID++;
}

DrawableObject::DrawableObject(int l, sf::Vector2f pos)
{
	myClasses.push_back("GameObject");
	myClasses.push_back("DrawableObject");
	layer = l;
	this->pos = pos;
	objID = nextID++;
}

DrawableObject::DrawableObject(int l, sf::Vector2f pos, std::string textureName)
{
	myClasses.push_back("GameObject");
	myClasses.push_back("DrawableObject");
	layer = l;
	this->pos = pos;

	sf::Sprite tempSprite(textures[textureName]);
	tempSprite.setPosition(pos);
	sprites.push_back(tempSprite);

	objID = nextID++;
}

void DrawableObject::updateSelf(sf::RenderWindow& w, sf::Time d) const
{
}

void DrawableObject::drawSelf(sf::RenderWindow& w) const
{
	for (const auto& spr : sprites)
	{
		w.draw(spr);
	}
}
