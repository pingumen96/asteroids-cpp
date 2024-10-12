#include "GameUI.h"

GameUI::GameUI() {
    // Carica il font (assicurati di avere un file .ttf disponibile)
    if (!font.loadFromFile("res/Atari.ttf")) {
        // Gestisci errore di caricamento
    }

    // Configura il testo del punteggio
    scoreText.setFont(font);
    scoreText.setCharacterSize(24); // Dimensione del testo
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10); // Posizione in alto a sinistra dello schermo
}

void GameUI::setScore(int newScore) {    
    score = newScore;
    scoreText.setString("Score: " + std::to_string(score)); // Aggiorna il testo
}

void GameUI::draw(sf::RenderWindow& window) {
    window.draw(scoreText); // Disegna il testo del punteggio
}
