#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>


class GameEngine;

/// @brief Klasa reprezentujπca obiekt gry
class GameObject
{
public:
	/// @brief Konstrukto domyúlny.
	GameObject();
	/// @brief Konstruktor z opcjπ ustalenia warstwy, na ktÛrej znajduje siÍ obiekt.
	/// @param l Warstwa
	GameObject(int l);

	/// @brief Konstruktor kopiujπcy
	/// @param other èrÛd≥owy obiekt
	GameObject(const GameObject& other) : layer(other.layer), pos(other.pos), myClasses(other.myClasses), engine(other.engine)
	{
		objID = nextID++;
	}

	/// @brief Dekonstruktor
	virtual ~GameObject() {}

	GameEngine* engine;	///< Wskaünik na silnik

	unsigned long long objID;	///< ID obiektu
	int layer;	///< Warstwa obiektu
	mutable sf::Vector2f pos;	///< Pozycja na ekranie

	/// @brief Zwraca ID obiektu
	/// @return ID obiektu
	unsigned long long getID() { return objID; };

	std::vector<std::string> myClasses;	///< Vector zawierajπcy nazwy klas, do ktÛrych naleøy obiekt
	/// @brief Sprawdza czy obiekt naleøy do zadanej klasy
	/// @param classname Nazwa klasy
	/// @return Wynik testu - prawda lub fa≥sz
	bool isInClass(std::string classname) const;

	/// @brief Aktualizacja w≥asnych wartoúci, w≥asnej logiki, itp.
	/// @param w Okno renderowania
	/// @param d Czas klatki
	virtual void updateSelf(sf::RenderWindow& w, sf::Time d) const { };
	/// @brief Rysowanie siÍ na ekranie
	/// @param w Okno renderowania
	virtual void drawSelf(sf::RenderWindow& w) const { };

	/// @brief Komparator warstw dwÛch obiektÛw - wykorzystywany w celu umieszczania obiektÛw w liúcie obiektÛw w sposÛb posegregowany
	struct CompareObjects {
		/// @brief Komparator dwÛch obiektÛw wed≥ug warstwy
		/// @param obj1 Lewy obiekt
		/// @param obj2 Prawy obiekt
		/// @return WartoúÊ true, jeúli l-obiekt ma niøszπ warstwÍ, false, jeúli to r-obiekt
		bool operator()(const GameObject* obj1, const GameObject* obj2) const {
			return obj1->layer < obj2->layer;
		}
	};

	static int nextID;	///< Zmienna pomagajπca przypisaÊ niepowtarzalnπ wartoúÊ ID do nowych obiektÛw
};

extern std::map<std::string, sf::Texture> textures;
