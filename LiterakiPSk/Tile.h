#pragma once
#include "DrawableObject.h"
#include <utility>

/// @brief Klasa reprezentuj¹ca p³ytki
class Tile :
    public DrawableObject
{
public:
    /// @brief Konstruktor g³ówny
    Tile();
    /// @brief Konstruktor z opcj¹ przypisania pozycji i tekstury
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    Tile(sf::Vector2f pos, std::string textureName);
    /// @brief Konstruktor z opcj¹ przypisania warstwy
    /// @param l Wartoœæ warstwy
    Tile(int l);
    /// @brief Konstruktor z opcj¹ przypisania warstwy, pozycji i tekstury
    /// @param l 
    /// @param pos 
    /// @param textureName 
    Tile(int l, sf::Vector2f pos, std::string textureName);

    /// @brief Konstruktor kopiuj¹cy
    /// @param other Obiekt Ÿród³ówy
    Tile(const Tile& other) : DrawableObject(other) {}

    unsigned int rackPos;   ///< Pozycja na stojaku
    sf::Vector2i boardPos = { -1, -1 }; ///< Pozycja na planszy

    std::pair<wchar_t, unsigned int> letterLogic;   ///< Litera p³ytki
    sf::Text letterVisual;  ///< Litera wyœwietlana na p³ytce
    sf::Vector2f letterDisplace;    ///< Przesuniêcie litery wobec punktu zerowego p³ytki

    /// @brief Rysowanie siê na ekranie
    /// @param w Okno renderowania
    void drawSelf(sf::RenderWindow& w) const override;
};

