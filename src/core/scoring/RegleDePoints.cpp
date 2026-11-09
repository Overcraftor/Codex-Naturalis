#include "RegleDePoints.h"
#include "board/Manuscrit.h"

#include <array>

int PointsFixes::calculer(const Manuscrit& m, const Placement& p) const {
    return valeur;
}

int PointsParObjet::calculer(const Manuscrit& m, const Placement& p) const {
    return valeur * m.compter(objetCible);
}

int PointsParCoinRecouvert::calculer(const Manuscrit& m, const Placement& p) const {
    int nb = 0;
    for (const auto& [coords, coinCible] : Manuscrit::getVoisins(p)) {
        const std::optional<Placement> voisin = m.getPlacement(coords.first, coords.second);
        // seules les cartes posees avant recouvrent un coin
        if (voisin.has_value() && voisin->ordre < p.ordre) {
            nb++;
        }
    }
    return valeur * nb;
}