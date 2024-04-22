#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>


class GameEngine;

/// @brief Klasa reprezentuj�ca obiekt gry
class GameObject
{
public:
	/// @brief Konstrukto domy�lny.
	GameObject();
	/// @brief Konstruktor z opcj� ustalenia warstwy, na kt�rej znajduje si� obiekt.
	/// @param l Warstwa
	GameObject(int l);

	/// @brief Konstruktor kopiuj�cy
	/// @param other �r�d�owy obiekt
	GameObject(const GameObject& other) : layer(other.layer), pos(other.pos), myClasses(other.myClasses), engine(other.engine)
	{
		objID = nextID++;
	}

	/// @brief Dekonstruktor
	virtual ~GameObject() {}

	GameEngine* engine;	///< Wska�nik na silnik

	unsigned long long objID;	///< ID obiektu
	int layer;	///< Warstwa obiektu
	mutable sf::Vector2f pos;	///< Pozycja na ekranie

	/// @brief Zwraca ID obiektu
	/// @return ID obiektu
	unsigned long long getID() { return objID; };

	std::vector<std::string> myClasses;	///< Vector zawieraj�cy nazwy klas, do kt�rych nale�y obiekt
	/// @brief Sprawdza czy obiekt nale�y do zadanej klasy
	/// @param classname Nazwa klasy
	/// @return Wynik testu - prawda lub fa�sz
	bool isInClass(std::string classname) const;

	/// @brief Aktualizacja w�asnych warto�ci, w�asnej logiki, itp.
	/// @param w Okno renderowania
	/// @param d Czas klatki
	virtual void updateSelf(sf::RenderWindow& w, sf::Time d) const { };
	/// @brief Rysowanie si� na ekranie
	/// @param w Okno renderowania
	virtual void drawSelf(sf::RenderWindow& w) const { };

	/// @brief Komparator warstw dw�ch obiekt�w - wykorzystywany w celu umieszczania obiekt�w w li�cie obiekt�w w spos�b posegregowany
	struct CompareObjects {
		/// @brief Komparator dw�ch obiekt�w wed�ug warstwy
		/// @param obj1 Lewy obiekt
		/// @param obj2 Prawy obiekt
		/// @return Warto�� true, je�li l-obiekt ma ni�sz� warstw�, false, je�li to r-obiekt
		bool operator()(const GameObject* obj1, const GameObject* obj2) const {
			return obj1->layer < obj2->layer;
		}
	};

	static int nextID;	///< Zmienna pomagaj�ca przypisa� niepowtarzaln� warto�� ID do nowych obiekt�w
};

extern std::map<std::string, sf::Texture> textures;
