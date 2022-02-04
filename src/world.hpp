#pragma once

#include <cstdlib>
#include <variant>
#include <iostream>
#include <ranges>
#include <array>
#include <vector>
#include <algorithm>
#include "cppmatrices.hpp"
#include "creature.hpp"
#include "food.hpp"
#include "space.hpp"
#include "direction.hpp"
#include "location.hpp"

constexpr double SPEED_SCALE_FACTOR = 3.0 / 50.0;

#define inrange(v) std::views::iota((std::size_t)0, (std::size_t)v)

class World {
    Matrix<Space> matrix;
    std::size_t turns;

   public:
    World(std::size_t width, std::size_t height) : matrix(width, height) {
        for (auto& space : matrix) {
            space = Space::random();
        }
    }

    auto show() const {
        matrix.show();
    }

    template <typename T>
    auto nearest(Location l) const -> Location {
        auto [row, col] = l;
        auto min_distance = std::numeric_limits<std::size_t>::max();
        
        auto best_point = Location{0, 0};

        for (std::size_t r = 0; r < matrix.get_rows(); ++r) {
            for (std::size_t c = 0; c < matrix.get_cols(); ++c) {
                if (std::holds_alternative<T>(matrix.get(r, c).contents) && r != row && c != col) {
                    std::size_t distance = std::abs((int64_t)r - (int64_t)row) + std::abs((int64_t)c - (int64_t)col);
                    if (distance < min_distance) {
                        min_distance = distance;
                        best_point = Location{r, c};
                    }
                }
            }
        }

        return best_point;
    }

    auto update() -> void {
        // each entity can decide what to do.
        // creatures either move or attack.
        // (attacking food means eating it)
        // a creature that is attacked on a
        // given turn cannot move on that turn.
        
        auto creatures = std::vector<Location>();
        creatures.reserve(100);
        for (std::size_t row : inrange(matrix.get_rows())) {
            for (std::size_t col : inrange(matrix.get_cols())) {
                if (std::holds_alternative<Creature>(matrix.get(row, col).contents)) {
                    creatures.emplace_back(row, col);
                }
            }
        }
        std::sort(creatures.begin(), creatures.end(), [this](auto l1, auto l2) {
            auto& c1 = std::get<Creature>(matrix.get(l1.row, l1.col).contents);
            auto& c2 = std::get<Creature>(matrix.get(l2.row, l2.col).contents);
            return c1.speed > c2.speed;
        });
        for (Location& l : creatures) {
            auto [row, col] = l;
            auto& space = matrix.get(row, col);
            auto creature = std::get<Creature>(space.contents);

            auto action = act(l, creature);
            auto new_loc = location_after_action(l, action);
            while (!std::holds_alternative<None>(matrix.get(new_loc.row, new_loc.col).contents) && action.distance != 0) {
                action.distance -= 1;
                new_loc = location_after_action(l, action);
            }
            auto [new_row, new_col] = new_loc;
            auto& new_space = matrix.get(new_row, new_col);
            space = Space();
            new_space = Space(creature);

            auto action2 = act(new_loc, creature);
            auto new_loc2 = location_after_action(new_loc, action2);
            while (!std::holds_alternative<None>(matrix.get(new_loc2.row, new_loc2.col).contents) && action2.distance != 0) {
                action2.distance -= 1;
                new_loc2 = location_after_action(new_loc, action2);
            }
            auto [new_row2, new_col2] = new_loc2;
            auto& new_space2 = matrix.get(new_row2, new_col2);
            new_space = Space();
            new_space2 = Space(creature);
        }
    }

    auto location_after_action(Location l, Action a) -> Location {
        auto [row, col] = l;
        auto [type, target, distance] = a;

        if (type == ATTACK) {
            return l;
        }

        auto direction = dir_from_to(l, target);

        switch (direction) {
            case UP:
                return Location{row - distance, col};
            case DOWN:
                return Location{row + distance, col};
            case LEFT:
                return Location{row, col - distance};
            case RIGHT:
                return Location{row, col + distance};
            default:
                std::exit(1);
        }
    }

    auto act(Location loc, Creature c) const -> Action {
        const auto creature_speed = (std::size_t)((double)c.speed * SPEED_SCALE_FACTOR + 0.5);
        auto decision = static_cast<std::size_t>(std::rand()) % 100;
        auto is_attacking = decision < c.aggression;
        Location target;
        std::size_t ortho_distance;
        if (is_attacking) {
            target = nearest<Creature>(loc);
            ortho_distance = Location::max_ortho_distance(loc, target);
        } else {
            target = nearest<Food>(loc);
            ortho_distance = Location::max_ortho_distance(loc, target);
        }
        if (Location::adjacent(loc, target)) {
            return Action::attack(target);
        } else {
            return Action::move(target, std::min(creature_speed, ortho_distance));
        }
    }
};