#pragma once

#include <SFML/Graphics.hpp>
#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <atomic>
#include <utility>

#include "Tile.h"
#include "Dictionary.h"
#include "LoadingScreen.h"

extern const int boardLetterBonuses[15][15];
extern const int boardWordBonuses[15][15];

extern std::map<std::string, sf::Texture> textures;
extern std::map<std::string, sf::Font> fonts;

extern int FULLRES_W;
extern int FULLRES_H;
extern double windowScale;
extern int windowW;
extern int windowH;

class GameObject;
class Tile;

/// @brief Klasa reprezentuj�ca silnik gry
class GameEngine
{
public:
	/// @brief Konstruktor domy�lny. Tworzy okno renderowania, za�adowuje s�ownik i zestaw liter.
	GameEngine();
	/// @brief Dekonstruktor. Usuwa istniej�ce obiekty.
	~GameEngine();

	/// @brief P�tla g��wna gry.
	void run();

	sf::RenderWindow mainWindow;	///< Okno renderowania
	sf::View view;	///< Widok okna

	int gameState = 0;	///Stan gry
	/*
		0	-	�adowanie
		1	-	przej�cie do gry
		2	-	gra
	*/

	Dictionary dictionary;	///< Obiekt s�ownika gry
	std::atomic<bool> isDictionaryLoaded;	///< Flaga za�adowania s�ownika

	std::vector<std::pair<wchar_t, unsigned int>> blueprintBag;	///< Wczytany zestaw liter
	std::vector<std::pair<wchar_t, unsigned int>> gameBag;	///< Zestaw liter u�ywany podczas rozgrywki

	std::multiset<GameObject*, GameObject::CompareObjects> objectSet;	///< Multiset zawieraj�cy wska�niki na obiekty gry
	Tile* playerRackTiles[2][7];	///< Tablica wska�nik�w na obiekty p�ytek na stojakach graczy
	Tile* onBoardTiles[7];	///< Tablica wska�nik�w na aktywne p�ytki na planszy
	LoadingScreen* loadScr;	///< Wska�nik na ekran �adowania.

	int activePlayer = 0;	///< Flaga aktywnego gracza
	Tile* heldTile = nullptr;	///< Wska�nik na podnision� p�ytk�

	/// @brief Dodanie obiektu do listy obiekt�w
	/// @param obj Wska�nik na obiekty
	void addObject(GameObject* obj);
	/// @brief Dodanie p�ytki do listy p�ytek
	/// @param player Numer gracza
	/// @param slot Miejsce na stojaku
	/// @param obj Wska�nik na obiekt p�ytki
	void addTile(int player, int slot, Tile* obj);

	/// @brief Rozdanie p�ytek graczom na pocz�tek gry
	void giveTiles();

private:
	sf::Event event;	///< Reprezentacja zdarzenia SFML

	sf::Clock gameClock;	///< Zegar gry
	sf::Time gameTime;	///< Czas gry
	sf::Time lastFrameTime = sf::Time::Zero;	///< Czas poprzedniej klatki
	sf::Time delta;	///< Czas ostatniej klatki
	
	/// @brief Przetwarzanie urz�dze� wej�ciowych
	void readInput();
	/// @brief Aktualizacja logiki gry
	void updateLogic();
	/// @brief Aktualizacja fizyki gry. Niewykorzystywane.
	void updatePhysics();
	/// @brief Aktualizacja warstwy graficznej.
	void updateGraphics();
	/// @brief Aktualizacja warstwy audio. Niewykorzystywane.
	void updateAudio();

};

