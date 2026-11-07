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

bool Manuscrit::peutPoser(const CartePiochable& c, bool recto, int x, int y) const {
    // la case est déjà occupée
    if (grille.find({x, y}) != grille.end()) {
        return false;
    }

    bool posable = false;

    // voisine en bas à droite : on recouvre son coin HG
    if (grille.find({x+1, y-1}) != grille.end()) {
        if (grille.at({x+1, y-1}).recto) {
            if (!grille.at({x+1, y-1}).carte->getRecto().getCoin(PositionCoin::HG).isVisible()) return false;
        } else {
            if (!grille.at({x+1, y-1}).carte->getVerso().getCoin(PositionCoin::HG).isVisible()) return false;
        }
        posable = true;
    }

    // voisine en bas à gauche : on recouvre son coin HD
    if (grille.find({x-1, y-1}) != grille.end()) {
        if (grille.at({x-1, y-1}).recto) {
            if (!grille.at({x-1, y-1}).carte->getRecto().getCoin(PositionCoin::HD).isVisible()) return false;
        } else {
            if (!grille.at({x-1, y-1}).carte->getVerso().getCoin(PositionCoin::HD).isVisible()) return false;
        }
        posable = true;
    }

    // voisine en haut à droite : on recouvre son coin BG
    if (grille.find({x+1, y+1}) != grille.end()) {
        if (grille.at({x+1, y+1}).recto) {
            if (!grille.at({x+1, y+1}).carte->getRecto().getCoin(PositionCoin::BG).isVisible()) return false;
        } else {
            if (!grille.at({x+1, y+1}).carte->getVerso().getCoin(PositionCoin::BG).isVisible()) return false;
        }
        posable = true;
    }

    // voisine en haut à gauche : on recouvre son coin BD
    if (grille.find({x-1, y+1}) != grille.end()) {
        if (grille.at({x-1, y+1}).recto) {
            if (!grille.at({x-1, y+1}).carte->getRecto().getCoin(PositionCoin::BD).isVisible()) return false;
        } else {
            if (!grille.at({x-1, y+1}).carte->getVerso().getCoin(PositionCoin::BD).isVisible()) return false;
        }
        posable = true;
    }

    // la carte ne touche aucune autre carte
    if (!posable) return false;


    // coût : seulement si la carte est posée recto (vide pour les cartes non dorées)
    if (recto) {
        std::map<Resource, int> besoin;
        for (Resource r : c.getRecto().getCout())
            besoin[r]++;                        // ex. {champignon: 3, animal: 1}

        for (const auto& [ressource, nombre] : besoin)
            if (compter(ressource) < nombre) return false;   // pas assez de cette ressource
    }
    return true;
}

void Manuscrit::poser(const CartePiochable& c, const bool recto, int x, int y) {
    if (!peutPoser(c, recto, x, y)) {
        throw std::invalid_argument("Placement invalide.");
    }

    const Placement p = { &c, x, y, recto, compteurOrdre++ };
    grille[{x, y}] = p;

    
    // mettre à jour l'inventaire et ressources
}
