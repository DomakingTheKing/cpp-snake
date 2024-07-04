//
// Created by domak on 04/07/2024.
//

#include "soundengine.hpp"

SoundEngine::SoundEngine() {

}

sf::Sound SoundEngine::getSound(const sf::String& fileName, int volume) {
    sf::Sound sound;
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("assets/audio/sfx/" + fileName)) {
        // Gestisci l'errore
        std::cerr << "Errore nel caricamento del file audio" << std::endl;
    } else {
        sound.setBuffer(buffer);
        sound.setVolume(volume);
    }

    return sound;
}

