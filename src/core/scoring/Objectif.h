#pragma once

#include <map>
#include <utility>
#include <vector>
#include "Types.h"

class Manuscrit;

class Objectif {
protected:
    int points;

public:
    explicit Objectif(const int pts) : points(pts) {}
    virtual ~Objectif() = default;

    // nombre de points gagnes a la fin de la partie
    virtual int evaluer(const Manuscrit& m) const = 0;

    int getPoints() const { return points; }
};


class ObjectifRessources : public Objectif {
    Resource ressource;
    int quantite;

public:
    ObjectifRessources(const int pts, const Resource r, const int qte = 3)
        : Objectif(pts), ressource(r), quantite(qte) {}

    int evaluer(const Manuscrit& m) const override;
};

class ObjectifObjets : public Objectif {
    std::vector<Object> objets;

public:
    ObjectifObjets(const int pts, std::vector<Object> objs)
        : Objectif(pts), objets(std::move(objs)) {}

    int evaluer(const Manuscrit& m) const override;
};


// un motif = 3 cartes : un decalage (dx, dy) par rapport a la premiere carte et le regne attendu
struct CaseMotif {
    int dx;
    int dy;
    Resource regne;
};

class ObjectifMotif : public Objectif {
    std::vector<CaseMotif> motif;

public:
    ObjectifMotif(const int pts, std::vector<CaseMotif> cases)
        : Objectif(pts), motif(std::move(cases)) {}

    int evaluer(const Manuscrit& m) const override;
};