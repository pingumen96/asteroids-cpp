#pragma once

#include <SFML/Audio.hpp>
#include <string>

class MusicManager {
public:
    MusicManager();

    // Carica le tracce musicali
    bool loadMusic(const std::string& normalTrack, const std::string& intenseTrack);

    // Riproduci la musica in base allo stato del gioco
    void playNormal();
    void playIntense();

    // Funzione da chiamare nel ciclo di gioco per gestire le transizioni
    void update(float deltaTime);

    // Gestisci la transizione con un fade tra le tracce
    void transitionToIntense();
    void transitionToNormal();

private:
    sf::Music normalMusic;
    sf::Music intenseMusic;
    sf::Music* currentMusic;
    sf::Music* nextMusic;

    float currentVolume;
    float targetVolume;
    float fadeSpeed;
    bool transitioning;
};
#pragma once
