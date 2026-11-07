#include "RegleDePoints.h"
#include "board/Manuscrit.h"

int PointsFixes::calculer(const Manuscrit& m, const Placement& p) const {
    return valeur;
}

int PointsParObjet::calculer(const Manuscrit& m, const Placement& p) const {
    // todo
}

int PointsParCoinRecouvert::calculer(const Manuscrit& m, const Placement& p) const {
    const int dx[4] = {-1, 1, -1, 1};
    const int dy[4] = {-1, -1, 1, 1};

    int nb = 0;
    for (int i = 0; i < 4; i++) {
        const Placement* voisin = m.getPlacement(p.x + dx[i], p.y + dy[i]);
        // seules les cartes posees avant recouvrent un coin
        if (voisin != nullptr && voisin->ordre < p.ordre) {
            nb++;
        }
    }
    return valeur * nb;
}