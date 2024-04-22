#pragma once
#include "GameObject.h"
#include <vector>

/// @brief Klasa reprezentuj¹ca obiekt rysowalny.
class DrawableObject :
    public GameObject
{
public:
    /// @brief Konstruktor domyœlny
    DrawableObject();
    /// @brief Konstruktor z opcj¹ przypisania tekstury
    /// @param textureName Nazwa tekstury
    DrawableObject(std::string textureName);
    /// @brief Konstruktor z opcj¹ przypisania pozycji
    /// @param pos Pozycja na ekranie
    DrawableObject(sf::Vector2f pos);
    /// @brief Konstruktor z opcj¹ przypisania tekstury i pozycji
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    DrawableObject(sf::Vector2f pos, std::string textureName);
    /// @brief  Konstruktor z opcj¹ przypisania warstwy.
    /// @param l Wartoœæ warstwy
    DrawableObject(int l);
    /// @brief Konstruktor z opcj¹ przypisania warstwy i tekstury
    /// @param l Wartoœæ warstwy
    /// @param textureName Nazwa tekstury
    DrawableObject(int l, std::string textureName);
    /// @brief Konstruktor z opcj¹ przypisania warstwy i pozycji
    /// @param l Wartoœæ warstwy
    /// @param pos Pozycja na ekranie
    DrawableObject(int l, sf::Vector2f pos);
    /// @brief Konstruktor z opcj¹ przypisania warstwy, pozycji i tekstury
    /// @param l Wartoœæ warstwy
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    DrawableObject(int l, sf::Vector2f pos, std::string textureName);

    /// @brief Konstruktor kopiuj¹cy
    /// @param other Obiekt Ÿród³owy
    DrawableObject(const DrawableObject& other) : GameObject(other){}

    /// @brief Aktualizacja w³asnych wartoœci, w³asnej logiki, itp.
    /// @param w Okno renderowania
    /// @param d Czas klatki
    void updateSelf(sf::RenderWindow& w, sf::Time d) const override;

    /// @brief Rysowanie siê na ekranie
    /// @param w Okno renderowania
    void drawSelf(sf::RenderWindow& w) const override;

    mutable std::vector<sf::Sprite> sprites;    ///< Vector zawieraj¹cy duszki wykorzystywane przez obiekt

    mutable double speed = 0;   ///< Prêdkoœæ obiektu

private:
    
};

extern double windowScale;