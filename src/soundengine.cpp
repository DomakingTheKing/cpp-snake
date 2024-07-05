#include <thread>
#include "soundengine.hpp"

// Define the global sound variables
shared_ptr<Sound> changeDirectionSfx;
shared_ptr<Sound> eatAppleSfx;
shared_ptr<Sound> crowdBooLoseSfx;
shared_ptr<Sound> bonkSfx;

shared_ptr<Sound> mainOst;

SoundEngine::SoundEngine() {
    changeDirectionSfx = getSound("sfx/change_direction.wav", 30.0f);
    eatAppleSfx = getSound("sfx/eat_apple.wav", 80.0f);
    crowdBooLoseSfx = getSound("sfx/crowd_boo_lose.wav", 100.0f);
    bonkSfx = getSound("sfx/bonk.wav", 80.0f);

    mainOst = getSound("ost/main.wav", 90.0f);
}

shared_ptr<Sound> SoundEngine::getSound(const String& fileName, float volume) {
    auto sound = make_shared<Sound>();
    auto buffer = make_shared<SoundBuffer>();
    if (!buffer->loadFromFile("assets/audio/" + fileName)) {
        cerr << "Error loading sound file: " << fileName.toAnsiString() << endl;
        return nullptr;
    }
    sound->setBuffer(*buffer);
    sound->setVolume(volume);
    activeBuffers.push_back(buffer); // Keep the buffer alive
    return sound;
}

void SoundEngine::playSound(shared_ptr<Sound> sound) {
    lock_guard<mutex> lock(soundMutex);
    sound->play();
    activeSounds.push_back(sound);
}

void SoundEngine::stopSound(shared_ptr<Sound> sound) {
    lock_guard<mutex> lock(soundMutex);
    sound->stop();
    activeSounds.remove(sound);
}

void SoundEngine::fadeOutAndStopSound(shared_ptr<Sound> sound, float duration) {
    thread([this, sound, duration]() {
        float initialVolume = sound->getVolume();
        int steps = 30;
        float stepDuration = duration / steps;
        float volumeStep = initialVolume / steps;

        for (int i = 0; i < steps; ++i) {
            {
                lock_guard<mutex> lock(soundMutex);
                sound->setVolume(initialVolume - volumeStep * i);
            }
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(stepDuration * 1000)));
        }

        {
            lock_guard<mutex> lock(soundMutex);
            sound->stop();
            activeSounds.remove(sound);
        }

        cout << "finito";
    }).detach();
}

shared_ptr<Sound> SoundEngine::getEatAppleSfx() {
    return eatAppleSfx;
}

shared_ptr<Sound> SoundEngine::getChangeDirectionSfx() {
    return changeDirectionSfx;
}

shared_ptr<Sound> SoundEngine::getCrowdBooLoseSfx() {
    return crowdBooLoseSfx;
}

shared_ptr<Sound> SoundEngine::getBonkSfx() {
    return bonkSfx;
}

shared_ptr<Sound> SoundEngine::getMainOst() {
    return mainOst;
}
