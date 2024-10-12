#include "MusicManager.h"

MusicManager::MusicManager()
    : currentMusic(nullptr), nextMusic(nullptr), currentVolume(100.f), targetVolume(100.f), fadeSpeed(20.f), transitioning(false) {
}

bool MusicManager::loadMusic(const std::string& normalTrack, const std::string& intenseTrack) {
    if (!normalMusic.openFromFile(normalTrack)) {
        return false;
    }
    if (!intenseMusic.openFromFile(intenseTrack)) {
        return false;
    }
    normalMusic.setLoop(true);
    intenseMusic.setLoop(true);
    return true;
}

void MusicManager::playNormal() {
    normalMusic.play();
    currentMusic = &normalMusic;
    nextMusic = nullptr;
    transitioning = false;
}

void MusicManager::playIntense() {
    intenseMusic.play();
    currentMusic = &intenseMusic;
    nextMusic = nullptr;
    transitioning = false;
}

void MusicManager::transitionToIntense() {
    nextMusic = &intenseMusic;
    nextMusic->play();
    nextMusic->setVolume(0);
    targetVolume = 100.f;
    currentVolume = 100.f;
    transitioning = true;
}

void MusicManager::transitionToNormal() {
    nextMusic = &normalMusic;
    nextMusic->play();
    nextMusic->setVolume(0);
    targetVolume = 100.f;
    currentVolume = 100.f;
    transitioning = true;
}

void MusicManager::update(float deltaTime) {
    if (transitioning && currentMusic && nextMusic) {
        currentVolume -= fadeSpeed * deltaTime;
        nextMusic->setVolume(100.f - currentVolume);
        currentMusic->setVolume(currentVolume);

        if (currentVolume <= 0.f) {
            currentMusic->stop();
            currentMusic = nextMusic;
            nextMusic = nullptr;
            transitioning = false;
        }
    }
}
