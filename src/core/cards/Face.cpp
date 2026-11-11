#include "Face.h"
#include <stdexcept>
#include <utility>

#include "scoring/RegleDePoints.h"

Face::Face(const std::array<Coin, 4>& coins_in,
           std::vector<Resource> center_in,
           std::vector<Resource> cost_in,
           RegleDePoints* rule)
    : coins(coins_in),
      center(std::move(center_in)),
      cost(std::move(cost_in)),
      rule(rule)
{
    if (center.size() > 3) throw std::invalid_argument("Trop de ressources au centre (max 3)");
    if (cost.size() > 5) throw std::invalid_argument("Coût trop élevé (max 5)");
}

const std::array<Coin, 4>& Face::getCoins() const { return coins; }

const Coin& Face::getCoin(PositionCoin pos) const {
    return coins.at(static_cast<std::size_t>(pos));
}

const std::vector<Resource>& Face::getCentre() const { return center; }
const std::vector<Resource>& Face::getCout() const { return cost; }

int Face::getPoints(const Manuscrit& m, const Placement& p) const
{
    if (rule == nullptr)
        return 0;
    return rule->calculer(m, p);
}
