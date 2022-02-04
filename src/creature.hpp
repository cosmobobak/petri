#pragma once

#include <cstdlib>
#include <iostream>
#include <utility>
#include "action.hpp"
#include "location.hpp"

struct Creature {
    std::size_t speed;
    std::size_t attack;
    std::size_t range;
    std::size_t size;
    std::size_t aggression;

    Creature() : speed(0), attack(0), range(0), size(0), aggression(0) {}

    Creature(std::size_t speed, std::size_t attack, std::size_t range, std::size_t size)
        : speed(speed), attack(attack), range(range), size(size) {}

    static auto create(std::size_t speed, std::size_t attack, std::size_t range, std::size_t size) -> Creature {
        return Creature(speed, attack, range, size);
    }

    static auto random() -> Creature {
        return Creature(
            std::rand() % 100 + 1,
            std::rand() % 100 + 1,
            std::rand() % 100 + 1,
            std::rand() % 100 + 1
        );
    }

    static auto default_creature() -> Creature {
        return Creature(
            50,
            50,
            50,
            50
        );
    }

    auto hunger() const -> std::size_t {
        return (speed + attack + range + size) / 4;
    }

    auto toughness() const -> std::size_t {
        return size * 2;
    }

    auto show() const {
        printf("speed: %zu\n", speed);
        printf("hunger: %zu\n", hunger());
        printf("attack: %zu\n", attack);
        printf("range: %zu\n", range);
        printf("toughness: %zu\n", toughness());
        printf("size: %zu\n", size);
        printf("aggression: %zu\n", aggression);
    }
};