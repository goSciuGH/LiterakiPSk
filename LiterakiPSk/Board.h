#pragma once
#include "DrawableObject.h"

/// @brief Klasa reprezentuj�ca plansz� gry.
class Board :
    public DrawableObject
{
public:
    /// @brief Konstruktor domy�lny
    Board();
    /// @brief Konstruktor z opcj� przypisania pozycji i tekstury
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    Board(sf::Vector2f pos, std::string textureName);
    /// @brief Konstruktor z opcj� przypisania warstwy
    /// @param l Warto�� warstwy
    Board(int l);
    /// @brief Konstruktor z opcj� przypisania warstwy, pozycji i tekstury
    /// @param l Warto�� warstwy
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    Board(int l, sf::Vector2f pos, std::string textureName);

    /// @brief Konstruktor kopiuj�cy
    /// @param other Obiekt �r�d�owy
    Board(const Board& other) : DrawableObject(other) {}
};

