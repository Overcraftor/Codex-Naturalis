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

    bool peutPoser(const CartePiochable& c, bool recto, int x, int y) const;
    void poser(const CartePiochable& c, bool recto, int x, int y);
};