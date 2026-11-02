#pragma once
#include <optional>

#include "Types.h"

class Coin
{
    PositionCoin position;
    bool visible;

    std::optional<Resource> resource;
    std::optional<Object> object;

public:
    Coin(PositionCoin coin, bool vis, std::optional<Resource> res = std::nullopt, std::optional<Object> obj = std::nullopt);

    // getters
    PositionCoin getPosition() const;
    bool isVisible() const;
    std::optional<Resource> getResource() const;
    std::optional<Object> getObjet() const;
};