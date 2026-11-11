#pragma once

#include <array>
#include <vector>
#include "Types.h"
#include "cards/Coin.h"
#include "scoring/RegleDePoints.h"

class Manuscrit;
struct Placement;

class Face {
    std::array<Coin, 4> coins;

    std::vector<Resource> center;
    std::vector<Resource> cost;

    RegleDePoints* rule;

public:
    ~Face() { delete rule; }

    Face(const Face&) = delete;
    Face& operator=(const Face&) = delete;
    explicit Face(const std::array<Coin, 4>& coins,
                  std::vector<Resource> centre = {},
                  std::vector<Resource> cost = {},
                  RegleDePoints* rule = nullptr);

    // getters
    const std::array<Coin, 4>& getCoins() const;
    const Coin& getCoin(PositionCoin pos) const;
    const std::vector<Resource>& getCentre() const;
    const std::vector<Resource>& getCout() const;
    int getPoints(const Manuscrit& m, const Placement& p) const;
};