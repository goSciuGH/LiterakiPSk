#pragma once

#include "DrawableObject.h"

/// @brief Klasa reprezentuj¹ca ekran ³adowania
class LoadingScreen :
    public DrawableObject
{
public:
    /// @brief Konstruktor domyœlny
    LoadingScreen();
    /// @brief Konstruktor z opcj¹ przypisania pozycji i tekstury
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    LoadingScreen(sf::Vector2f pos, std::string textureName);
    /// @brief Konstruktor z opcj¹ przypisania warstwy
    /// @param l Wartoœæ warstwy
    LoadingScreen(int l);
    /// @brief Konstruktor z opcj¹ przypisania warstwy, pozycji i tekstury
    /// @param l Wartoœæ warstwy
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    LoadingScreen(int l, sf::Vector2f pos, std::string textureName);

    /// @brief Konstruktor kopiuj¹cy
    /// @param other Obiekt Ÿród³owy
    LoadingScreen(const LoadingScreen& other) : DrawableObject(other) {}

    /// @brief Aktualizacja w³asnych wartoœci, w³asnej logiki, itp.
    /// @param w Okno renderowania
    /// @param d Czas klatki
    void updateSelf(sf::RenderWindow& w, sf::Time d) const override;

    mutable bool isReady = true;    ///< Flaga zakoñczenia ³adowania
};

