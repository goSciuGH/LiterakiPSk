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

/// @brief Klasa reprezentuj¹ca silnik gry
class GameEngine
{
public:
	/// @brief Konstruktor domyœlny. Tworzy okno renderowania, za³adowuje s³ownik i zestaw liter.
	GameEngine();
	/// @brief Dekonstruktor. Usuwa istniej¹ce obiekty.
	~GameEngine();

	/// @brief Pêtla g³ówna gry.
	void run();

	sf::RenderWindow mainWindow;	///< Okno renderowania
	sf::View view;	///< Widok okna

	int gameState = 0;	///Stan gry
	/*
		0	-	³adowanie
		1	-	przejœcie do gry
		2	-	gra
	*/

	Dictionary dictionary;	///< Obiekt s³ownika gry
	std::atomic<bool> isDictionaryLoaded;	///< Flaga za³adowania s³ownika

	std::vector<std::pair<wchar_t, unsigned int>> blueprintBag;	///< Wczytany zestaw liter
	std::vector<std::pair<wchar_t, unsigned int>> gameBag;	///< Zestaw liter u¿ywany podczas rozgrywki

	std::multiset<GameObject*, GameObject::CompareObjects> objectSet;	///< Multiset zawieraj¹cy wskaŸniki na obiekty gry
	Tile* playerRackTiles[2][7];	///< Tablica wskaŸników na obiekty p³ytek na stojakach graczy
	Tile* onBoardTiles[7];	///< Tablica wskaŸników na aktywne p³ytki na planszy
	LoadingScreen* loadScr;	///< WskaŸnik na ekran ³adowania.

	int activePlayer = 0;	///< Flaga aktywnego gracza
	Tile* heldTile = nullptr;	///< WskaŸnik na podnision¹ p³ytkê

	/// @brief Dodanie obiektu do listy obiektów
	/// @param obj WskaŸnik na obiekty
	void addObject(GameObject* obj);
	/// @brief Dodanie p³ytki do listy p³ytek
	/// @param player Numer gracza
	/// @param slot Miejsce na stojaku
	/// @param obj WskaŸnik na obiekt p³ytki
	void addTile(int player, int slot, Tile* obj);

	/// @brief Rozdanie p³ytek graczom na pocz¹tek gry
	void giveTiles();

private:
	sf::Event event;	///< Reprezentacja zdarzenia SFML

	sf::Clock gameClock;	///< Zegar gry
	sf::Time gameTime;	///< Czas gry
	sf::Time lastFrameTime = sf::Time::Zero;	///< Czas poprzedniej klatki
	sf::Time delta;	///< Czas ostatniej klatki
	
	/// @brief Przetwarzanie urz¹dzeñ wejœciowych
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

