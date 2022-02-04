#pragma once

#include <cstdlib>
#include "location.hpp"

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

auto dir_from_to(Location l1, Location l2) -> Direction {
    auto [r1, c1] = l1;
    auto [r2, c2] = l2;
    std::size_t horizontal_diff = std::abs((int64_t)r1 - (int64_t)r2);
    std::size_t vertical_diff = std::abs((int64_t)c1 - (int64_t)c2);

    if (horizontal_diff > vertical_diff) {
        if (r1 > r2) {
            return LEFT;
        } else {
            return RIGHT;
        }
    } else {
        if (c1 > c2) {
            return UP;
        } else {
            return DOWN;
        }
    }
}