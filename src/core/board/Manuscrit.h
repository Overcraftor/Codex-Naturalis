#pragma once

#include <map>
#include <optional>
#include <utility>
#include "Types.h"

class Carte;

struct Placement {
    const Carte* carte;
    int x;
    int y;
    bool recto;
    int ordre;
};

class Manuscrit {
    // std::pair tuple de 2 items
    std::map<std::pair<int, int>, Placement> grille;

    std::map<Resource, int> inventaireRessources;
    std::map<Object, int> inventaireObjets;

    // pour compter les cartes et savoir lesquelles sont en dessous/dessus
    int compteurOrdre = 0;

public:
    Manuscrit() = default;
    ~Manuscrit() = default;

    int compter(Resource r) const;
    int compter(Object o) const;

    bool peutPoser(const Carte& c, bool recto, int x, int y) const;
    bool estOccupe(int x, int y) const;
    std::optional<Placement> getPlacement(int x, int y) const;
    const std::map<std::pair<int, int>, Placement>& getGrille() const { return grille; }
    void poser(const Carte& c, bool recto, int x, int y);

    static std::array<std::pair<std::pair<int ,int>, PositionCoin>, 4> getVoisins(const Placement& p);
    static std::array<std::pair<std::pair<int ,int>, PositionCoin>, 4> getVoisins(int x, int y);
};