#pragma once
#include "GameObject.h"
#include <vector>

/// @brief Klasa reprezentuj�ca obiekt rysowalny.
class DrawableObject :
    public GameObject
{
public:
    /// @brief Konstruktor domy�lny
    DrawableObject();
    /// @brief Konstruktor z opcj� przypisania tekstury
    /// @param textureName Nazwa tekstury
    DrawableObject(std::string textureName);
    /// @brief Konstruktor z opcj� przypisania pozycji
    /// @param pos Pozycja na ekranie
    DrawableObject(sf::Vector2f pos);
    /// @brief Konstruktor z opcj� przypisania tekstury i pozycji
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    DrawableObject(sf::Vector2f pos, std::string textureName);
    /// @brief  Konstruktor z opcj� przypisania warstwy.
    /// @param l Warto�� warstwy
    DrawableObject(int l);
    /// @brief Konstruktor z opcj� przypisania warstwy i tekstury
    /// @param l Warto�� warstwy
    /// @param textureName Nazwa tekstury
    DrawableObject(int l, std::string textureName);
    /// @brief Konstruktor z opcj� przypisania warstwy i pozycji
    /// @param l Warto�� warstwy
    /// @param pos Pozycja na ekranie
    DrawableObject(int l, sf::Vector2f pos);
    /// @brief Konstruktor z opcj� przypisania warstwy, pozycji i tekstury
    /// @param l Warto�� warstwy
    /// @param pos Pozycja na ekranie
    /// @param textureName Nazwa tekstury
    DrawableObject(int l, sf::Vector2f pos, std::string textureName);

    /// @brief Konstruktor kopiuj�cy
    /// @param other Obiekt �r�d�owy
    DrawableObject(const DrawableObject& other) : GameObject(other){}

    /// @brief Aktualizacja w�asnych warto�ci, w�asnej logiki, itp.
    /// @param w Okno renderowania
    /// @param d Czas klatki
    void updateSelf(sf::RenderWindow& w, sf::Time d) const override;

    /// @brief Rysowanie si� na ekranie
    /// @param w Okno renderowania
    void drawSelf(sf::RenderWindow& w) const override;

    mutable std::vector<sf::Sprite> sprites;    ///< Vector zawieraj�cy duszki wykorzystywane przez obiekt

    mutable double speed = 0;   ///< Pr�dko�� obiektu

private:
    
};

extern double windowScale;