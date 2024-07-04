#include "Engine.hpp"


int main() {
    srand(static_cast<unsigned int>(time(0)));

    Engine engine;
    engine.run();

    return 0;
}
