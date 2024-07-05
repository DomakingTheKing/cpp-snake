#include "Engine.hpp"
#include "soundengine.hpp"

SoundEngine soundEngine;
Engine engine;

int main() {
    soundEngine.getMainOst()->setLoop(true);
    soundEngine.playSound(soundEngine.getMainOst());

    engine.run();

    return 0;
}
