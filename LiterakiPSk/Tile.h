#pragma once
#include "DrawableObject.h"
#include <utility>

/// @brief Klasa reprezentuj�ca p�ytki
class Tile :
    public DrawableObject
{
public:
    /// @brief Konstruktor g��wny
    Tile();
    /// @brief Konstruktor z opcj� przypisania pozycji i tekstury
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    Tile(sf::Vector2f pos, std::string textureName);
    /// @brief Konstruktor z opcj� przypisania warstwy
    /// @param l Warto�� warstwy
    Tile(int l);
    /// @brief Konstruktor z opcj� przypisania warstwy, pozycji i tekstury
    /// @param l 
    /// @param pos 
    /// @param textureName 
    Tile(int l, sf::Vector2f pos, std::string textureName);

    /// @brief Konstruktor kopiuj�cy
    /// @param other Obiekt �r�d��wy
    Tile(const Tile& other) : DrawableObject(other) {}

    unsigned int rackPos;   ///< Pozycja na stojaku
    sf::Vector2i boardPos = { -1, -1 }; ///< Pozycja na planszy

    std::pair<wchar_t, unsigned int> letterLogic;   ///< Litera p�ytki
    sf::Text letterVisual;  ///< Litera wy�wietlana na p�ytce
    sf::Vector2f letterDisplace;    ///< Przesuni�cie litery wobec punktu zerowego p�ytki

    /// @brief Rysowanie si� na ekranie
    /// @param w Okno renderowania
    void drawSelf(sf::RenderWindow& w) const override;
};

