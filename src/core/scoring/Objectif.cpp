#include "Objectif.h"
#include "board/Manuscrit.h"

int ObjectifRessources::evaluer(const Manuscrit& m) const {
    // TODO : points * (nombre de ressources visibles / quantite)
    return 0;
}

int ObjectifObjets::evaluer(const Manuscrit& m) const {
    // TODO : points * nombre de groupes d'objets complets
    return 0;
}

int ObjectifMotif::evaluer(const Manuscrit& m) const {
    // TODO : points * nombre de motifs trouves dans le manuscrit (une carte ne compte qu'une fois)
    return 0;
}