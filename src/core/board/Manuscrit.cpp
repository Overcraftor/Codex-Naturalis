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
    if (grille.find({x, y}) != grille.end())
        return false;

    bool posable = false;
    for (const auto& [coords, coinCible] : getVoisins(x, y)) {
        const std::optional<Placement> voisin = getPlacement(coords.first, coords.second);
        if (voisin.has_value()) {
            // on récupère la face
            const Face& faceVoisine = voisin->recto ? voisin->carte->getRecto() : voisin->.carte->getVerso();

            // si le coin n'est pas visible, la carte n'est pas posable
            if (!faceVoisine.getCoin(coinCible).isVisible()) return false;

            posable = true;
        }
    }

    // la carte ne touche aucune autre carte
    if (!posable && !grille.empty()) return false;


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

void Manuscrit::poser(const Carte& c, const bool recto, int x, int y) {
    if (!peutPoser(c, recto, x, y)) {
        throw std::invalid_argument("Placement invalide.");
    }

    // il faut retirer les ressources des coins cachés par la nouvelle carte
    for (const auto& [coords, coinCible] : getVoisins(x, y)) {
        const std::optional<Placement> voisin = getPlacement(coords.first, coords.second);
        if (voisin.has_value()) {
            const Face& faceVoisine = voisin->recto ? voisin->carte->getRecto() : voisin->carte->getVerso();
            const Coin& coinRecouvert = faceVoisine.getCoin(coinCible);

            // On retire les éléments du coin qui disparaît sous la nouvelle carte
            if (coinRecouvert.getResource().has_value()) {
                inventaireRessources[coinRecouvert.getResource().value()]--;
            }
            if (coinRecouvert.getObjet().has_value()) {
                inventaireObjets[coinRecouvert.getObjet().value()]--;
            }
        }
    }

    // place la carte
    const Placement p = { &c, x, y, recto, compteurOrdre++ };
    grille[{x, y}] = p;

    const Face& nouvelleFace = recto ? c.getRecto() : c.getVerso();

    // ajout ressources au centre
    if (recto) {
        for (Resource r : nouvelleFace.getCentre()) {
            inventaireRessources[r]++;
        }
    }

    // ajout coins visibles de la nouvelle carte
    for (const Coin& coin : nouvelleFace.getCoins()) {
        if (coin.isVisible()) {
            if (coin.getResource().has_value()) {
                inventaireRessources[coin.getResource().value()]++;
            }
            if (coin.getObjet().has_value()) {
                inventaireObjets[coin.getObjet().value()]++;
            }
        }
    }
}

std::array<std::pair<std::pair<int ,int>, PositionCoin>, 4> Manuscrit::getVoisins(const Placement& p)
{
    return getVoisins(p.x, p.y);
}

std::array<std::pair<std::pair<int ,int>, PositionCoin>, 4> Manuscrit::getVoisins(int x, int y)
{
    return {{
        {{x+1, y-1}, PositionCoin::HG},
        {{x-1, y-1}, PositionCoin::HD},
        {{x+1, y+1}, PositionCoin::BG},
        {{x-1, y+1}, PositionCoin::BD}
    }};
}

bool Manuscrit::estOccupe(const int x, const int y) const {
    return grille.find({x, y}) != grille.end();
}

std::optional<Placement> Manuscrit::getPlacement(const int x, const int y) const {
    const auto it = grille.find({x, y});
    return (it != grille.end()) ? std::optional{it->second} : std::nullopt;
}
