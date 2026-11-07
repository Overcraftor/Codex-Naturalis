#include "RegleDePoints.h"
#include "board/Manuscrit.h"

int PointsFixes::calculer(const Manuscrit& m, const Placement& p) const {
    return valeur;
}

int PointsParObjet::calculer(const Manuscrit& m, const Placement& p) const {
    return valeur * m.compter(objetCible);
}

int PointsParCoinRecouvert::calculer(const Manuscrit& m, const Placement& p) const {
    
}