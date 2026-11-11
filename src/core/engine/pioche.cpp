#include "pioche.h"
#include <algorithm>
#include <random>
#include <stdexcept>

Pioche::Pioche(std::vector<const CartePiochable*> cartesInitiales) : reserve(std::move(cartesInitiales))
{
    // mélange du packet
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(reserve.begin(), reserve.end(), g);

    remplirMarche();
}

void Pioche::remplirMarche() {
    while (visibles.size() < 3 && !reserve.empty()) {
        visibles.push_back(reserve.back());
        reserve.pop_back();
    }
}

const CartePiochable* Pioche::piocher(const int index) {
    if (index < 0 || index >= visibles.size())
        throw std::out_of_range("Index de carte visible invalide.");


    const CartePiochable* carteChoisie = visibles[index];
    visibles.erase(visibles.begin() + index);
    
    remplirMarche();
    return carteChoisie;
}

bool Pioche::estVide() const {
    return reserve.empty() && visibles.empty();
}

int Pioche::getNbReserve() const {
    return  static_cast<int>(reserve.size());
}

const std::vector<const CartePiochable*>& Pioche::getVisibles() const {
    return visibles;
}

PiocheRessource::PiocheRessource(std::vector<const CartePiochable*> cartesInitiales)
    : Pioche(std::move(cartesInitiales))
{
}

PiocheDorure::PiocheDorure(std::vector<const CartePiochable*> cartesInitiales)
    : Pioche(std::move(cartesInitiales))
{
}