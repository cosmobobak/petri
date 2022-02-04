#pragma once

#include <cstdlib>

struct Food {
    std::size_t restored_amount;

    Food(std::size_t restored_amount) : restored_amount(restored_amount) {}
};