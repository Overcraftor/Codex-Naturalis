#include "Coin.h"
#include <stdexcept>

Coin::Coin(const PositionCoin pos, const bool vis, const std::optional<Resource> res, const std::optional<Object> obj)
    : position(pos), visible(vis), resource(res), object(obj)
{
    // visible = faux => ni ressource ni objet
    if (!visible && (resource.has_value() || object.has_value())) {
        throw std::invalid_argument("Erreur : Un coin invisible ne peut pas contenir de ressource ni d'objet.");
    }

    // ressource et objet ne sont jamais renseignés ensemble
    if (resource.has_value() && object.has_value()) {
        throw std::invalid_argument("Erreur : Un coin ne peut pas contenir à la fois une ressource et un objet.");
    }
}

PositionCoin Coin::getPosition() const {
    return position;
}

bool Coin::isVisible() const {
    return visible;
}

std::optional<Resource> Coin::getResource() const {
    return resource;
}

std::optional<Objet> Coin::getObjet() const {
    return object;
}