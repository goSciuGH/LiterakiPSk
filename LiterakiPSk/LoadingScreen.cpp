#include "LoadingScreen.h"
#include "GameEngine.h"

LoadingScreen::LoadingScreen() : DrawableObject()
{
	myClasses.push_back("LoadingScreen");
}

LoadingScreen::LoadingScreen(sf::Vector2f pos, std::string textureName) : DrawableObject(pos, textureName)
{
	myClasses.push_back("LoadingScreen");
}

LoadingScreen::LoadingScreen(int l) : DrawableObject(l)
{
	myClasses.push_back("LoadingScreen");
}

LoadingScreen::LoadingScreen(int l, sf::Vector2f pos, std::string textureName) : DrawableObject(l, pos, textureName)
{
	myClasses.push_back("LoadingScreen");
}

void LoadingScreen::updateSelf(sf::RenderWindow& w, sf::Time d) const
{
	if (engine->gameState > 0)
	{
		if (isReady)
		{
			engine->giveTiles();
			isReady = false;
		}

		float dT = d.asSeconds();

		float shift = speed * dT;
		pos += sf::Vector2f(0.0f, speed);
		
		for (auto& spr : sprites)
		{
			spr.move(sf::Vector2f(0.0f, speed));
		}

		speed += dT * 3.375f;

		if (pos.y >= 1080.0f)
		{
			engine->gameState = 2;
		}
	}
}
