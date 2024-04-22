#pragma once
#include "DrawableObject.h"

/// @brief Klasa reprezentuj¹ca planszê gry.
class Board :
    public DrawableObject
{
public:
    /// @brief Konstruktor domyœlny
    Board();
    /// @brief Konstruktor z opcj¹ przypisania pozycji i tekstury
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    Board(sf::Vector2f pos, std::string textureName);
    /// @brief Konstruktor z opcj¹ przypisania warstwy
    /// @param l Wartoœæ warstwy
    Board(int l);
    /// @brief Konstruktor z opcj¹ przypisania warstwy, pozycji i tekstury
    /// @param l Wartoœæ warstwy
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    Board(int l, sf::Vector2f pos, std::string textureName);

    /// @brief Konstruktor kopiuj¹cy
    /// @param other Obiekt Ÿród³owy
    Board(const Board& other) : DrawableObject(other) {}
};

