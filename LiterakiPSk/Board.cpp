#include "Board.h"

Board::Board() : DrawableObject()
{
	myClasses.push_back("Board");
}

Board::Board(sf::Vector2f pos, std::string textureName) : DrawableObject(pos, textureName)
{
	myClasses.push_back("Board");
}

Board::Board(int l) : DrawableObject(l)
{
	myClasses.push_back("Board");
}

Board::Board(int l, sf::Vector2f pos, std::string textureName) : DrawableObject(l, pos, textureName)
{
	myClasses.push_back("Board");
}
