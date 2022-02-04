#pragma once

#include <cstdlib>
#include <variant>

#include "creature.hpp"
#include "food.hpp"

using None = std::monostate;

struct Space {
    std::variant<None, Creature, Food> contents;

    Space() : contents(None{}) {}
    Space(Creature c) : contents(c) {}
    Space(Food f) : contents(f) {}

    static auto random() -> Space {
        auto decision = std::rand() % 100;
        if (decision < 5) {
            return Space(Creature::default_creature());
        } else if (decision < 20) {
            return Space(Food(std::rand() % 100 + 1));
        } else {
            return Space();
        }
    }

    auto to_string() const -> char {
        if (contents.index() == 0) {
            return '.';
        } else if (contents.index() == 1) {
            return 'C';
        } else {
            return 'F';
        }
    }
};