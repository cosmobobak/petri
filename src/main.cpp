#include <iostream>
#include <variant>
#include "cppmatrices.hpp"
#include "creature.hpp"
#include "space.hpp"
#include "world.hpp"

int main() {
    srand(time(nullptr));

    auto world = World(5, 5);

    world.show();

    int crap;
    while (true) {
        std::cin >> crap;
        world.update();
        world.show();
    }
}