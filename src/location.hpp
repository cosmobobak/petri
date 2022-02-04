#pragma once

#include <cstdlib>
#include <algorithm>

struct Location {
    std::size_t row;
    std::size_t col;

    static auto adjacent(Location l1, Location l2) -> bool {
        auto [r1, c1] = l1;
        auto [r2, c2] = l2;
        // only orthogonal
        return std::abs((int64_t)r1 - (int64_t)r2) + std::abs((int64_t)c1 - (int64_t)c2) == 1;
    }

    static auto max_ortho_distance(Location l1, Location l2) -> std::size_t {
        auto [r1, c1] = l1;
        auto [r2, c2] = l2;
        
        return std::max(std::abs((int64_t)r1 - (int64_t)r2), std::abs((int64_t)c1 - (int64_t)c2));
    }
};

