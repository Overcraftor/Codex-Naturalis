#pragma once

#include <map>
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
    std::map<std::pair<int, int>, Placement> grille;

    std::map<Resource, int> inventaireRessources;
    std::map<Object, int> inventaireObjets;

    int compteurOrdre = 0;

public:
    Manuscrit() = default;
    ~Manuscrit() = default;

    int compter(Resource r) const;
    int compter(Object o) const;

    bool peutPoser(const Carte& c, bool recto, int x, int y) const;
    void poser(const Carte& c, bool recto, int x, int y);
};