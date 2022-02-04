#pragma once

#include <cstdlib>
#include "direction.hpp"
#include "location.hpp"

enum ActionType {
    ATTACK = 0b01,
    MOVE = 0b10
};

struct Action {
    ActionType type;
    Location target;
    std::size_t distance;

    static auto attack(Location loc) -> Action {
        return Action{ATTACK, loc, 0};
    }

    static auto move(Location loc, std::size_t dist) -> Action {
        return Action{MOVE, loc, dist};
    }
};