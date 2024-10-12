#pragma once

#include <SFML/Graphics.hpp>

class GameUI {
public:
    GameUI();

    // Metodo per aggiornare il punteggio
    void setScore(int score);

    // Metodo per disegnare la UI
    void draw(sf::RenderWindow& window);

private:
    sf::Font font; // Font per il testo
    sf::Text scoreText; // Testo per il punteggio
    int score = 0; // Variabile per il punteggio
};
