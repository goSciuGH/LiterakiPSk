#pragma once

#include "DrawableObject.h"

/// @brief Klasa reprezentuj�ca ekran �adowania
class LoadingScreen :
    public DrawableObject
{
public:
    /// @brief Konstruktor domy�lny
    LoadingScreen();
    /// @brief Konstruktor z opcj� przypisania pozycji i tekstury
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    LoadingScreen(sf::Vector2f pos, std::string textureName);
    /// @brief Konstruktor z opcj� przypisania warstwy
    /// @param l Warto�� warstwy
    LoadingScreen(int l);
    /// @brief Konstruktor z opcj� przypisania warstwy, pozycji i tekstury
    /// @param l Warto�� warstwy
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    LoadingScreen(int l, sf::Vector2f pos, std::string textureName);

    /// @brief Konstruktor kopiuj�cy
    /// @param other Obiekt �r�d�owy
    LoadingScreen(const LoadingScreen& other) : DrawableObject(other) {}

    /// @brief Aktualizacja w�asnych warto�ci, w�asnej logiki, itp.
    /// @param w Okno renderowania
    /// @param d Czas klatki
    void updateSelf(sf::RenderWindow& w, sf::Time d) const override;

    mutable bool isReady = true;    ///< Flaga zako�czenia �adowania
};

