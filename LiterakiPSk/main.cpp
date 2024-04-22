#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <map>

#include <ctime>
#include <cstdlib>

#include <thread>
#include <atomic>
#include <unordered_map>
#include <fstream>

#include "GameEngine.h"
#include "LoadingScreen.h"
#include "Tile.h"

const int boardLetterBonuses[15][15] = {
	{5, 0, 0, 0, 0, 2, 0, 5, 0, 2, 0, 0, 0, 0, 5},
	{0, 0, 0, 0, 2, 0, 5, 0, 5, 0, 2, 0, 0, 0, 0},
	{0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0},
	{0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0},
	{0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0},
	{2, 0, 0, 0, 1, 0, 0, 3, 0, 0, 1, 0, 0, 0, 2},
	{0, 5, 0, 1, 0, 0, 3, 0, 3, 0, 0, 1, 0, 5, 0},
	{5, 0, 1, 0, 0, 3, 0, 5, 0, 3, 0, 0, 1, 0, 5},
	{0, 5, 0, 1, 0, 0, 3, 0, 3, 0, 0, 1, 0, 5, 0},
	{2, 0, 0, 0, 1, 0, 0, 3, 0, 0, 1, 0, 0, 0, 2},
	{0, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 2, 0},
	{0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0},
	{0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0},
	{0, 0, 0, 0, 2, 0, 5, 0, 5, 0, 2, 0, 0, 0, 0},
	{5, 0, 0, 0, 0, 2, 0, 5, 0, 2, 0, 0, 0, 0, 5}
};	///< Tablica reprezentuj�ca kolor p�l planszy, u�ywana do przyznawana premii za dopasowanie p�ytek

const int boardWordBonuses[15][15] = {
	{1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{3, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 3},
	{1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
	{1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
	{1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1},
	{1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1},
	{1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1},
	{3, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 3},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1}
};	///< Tablica reprezentuj�ca pola-mno�niki warto�ci s��w

int FULLRES_W = 1920;	///< Szeroko�� widoku w px.
int FULLRES_H = 1080;	///< Wysoko�� widoku w px.

bool fullScreen = false;	///< Opis stanu pe�nego okna.

double windowScale = 1.0 / 2.0;				///< Skala wy�wietlanego okna.
int windowW = FULLRES_W * windowScale;		///< Szeroko�� okna w px.
int windowH = FULLRES_H * windowScale;		///< Wysoko�� okna w px.


std::map<std::string, sf::Texture> textures;	///< Mapa przechowuj�ca tekstury
std::map<std::string, sf::Font> fonts;			///< Mapa przechowuj�ca czcionki

int GameObject::nextID = 1;	///< Zmienna pomagaj�ca przypisa� niepowtarzaln� warto�� ID do nowych obiekt�w

/// @brief Funkcja main() programu
/// @return Nic.
int main()
{
	srand(time(NULL));

	// load textures
	if (!textures["tileBase"].loadFromFile("sprites/spr_tileBase.png"))
	{
		std::cout << "Blad wczytywania duszka spr_tileBase\n";
	}
	if (!textures["playboard"].loadFromFile("sprites/spr_gameBoard.png"))
	{
		std::cout << "Blad wczytywania duszka spr_gameBoard\n";
	}
	if (!textures["loadScr"].loadFromFile("sprites/spr_loadScreen.png"))
	{
		std::cout << "Blad wczytywania duszka spr_loadScreen\n";
	}

	for (auto& pair : textures) {
		pair.second.setSmooth(true);
	}

	if (!fonts["Lexend"].loadFromFile("fonts/Lexend-VariableFont_wght.ttf"))
	{
		std::cout << "Blad wczytywania fontu Lexend\n";
	}

	GameEngine* mainEngine = new GameEngine();

	LoadingScreen* loadScr = new LoadingScreen(400, sf::Vector2f(0.0f, 0.0f), "loadScr");
	loadScr->engine = mainEngine;
	mainEngine->addObject(loadScr);
	mainEngine->loadScr = loadScr;

	while (mainEngine->mainWindow.isOpen())
	{
		mainEngine->run();
	}

	mainEngine->dictionary.waitForLoading();

	return 0;
}