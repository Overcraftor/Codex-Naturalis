#include "Manuscrit.h"
#include "cards/Carte.h"
#include <stdexcept>

int Manuscrit::compter(const Resource r) const {
    const auto it = inventaireRessources.find(r);
    return (it != inventaireRessources.end()) ? it->second : 0;
}

int Manuscrit::compter(const Object o) const {
    const auto it = inventaireObjets.find(o);
    return (it != inventaireObjets.end()) ? it->second : 0;
}

bool Manuscrit::peutPoser(const Carte& c, bool recto, int x, int y) const {
    // la case est déjà occupée
    if (grille.find({x, y}) != grille.end()) {
        return false;
    }

    // TODO
    // verifier si la carte recouvre bien un coin existant

    // vérifier que le coin est visible

    // vérifier d'avoir les ressources pour poser la carte
    // if (recto)..

    return true;
}

void Manuscrit::poser(const Carte& c, const bool recto, int x, int y) {
    if (!peutPoser(c, recto, x, y)) {
        throw std::invalid_argument("Placement invalide.");
    }

    const Placement p = { &c, x, y, recto, compteurOrdre++ };
    grille[{x, y}] = p;

    // mettre à jour l'inventaire et ressources
}

bool Manuscrit::estOccupe(const int x, const int y) const {
    return grille.find({x, y}) != grille.end();
}

const Placement* Manuscrit::getPlacement(const int x, const int y) const {
    const auto it = grille.find({x, y});
    return (it != grille.end()) ? &it->second : nullptr;
}
