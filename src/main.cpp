#include "Engine.hpp"
#include "soundengine.hpp"

SoundEngine soundEngine;
Engine engine;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    engine.run();

    return 0;
}
