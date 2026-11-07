#include "Carte.h"

#include <utility>

Carte::Carte(Face recto, Face verso)
    : recto(std::move(recto)), verso(std::move(verso))
{
}

const Face& Carte::getRecto() const {
    return recto;
}

const Face& Carte::getVerso() const {
    return verso;
}

CartePiochable::CartePiochable(Face recto, Face verso, const Resource r)
    : Carte(std::move(recto), std::move(verso)), regne(r)
{
}

Resource CartePiochable::getRegne() const {
    return regne;
}

CarteRessource::CarteRessource(Face recto, Face verso, const Resource r)
    : CartePiochable(std::move(recto), std::move(verso), r)
{
}

CarteDorure::CarteDorure(Face recto, Face verso, const Resource r)
    : CartePiochable(std::move(recto), std::move(verso), r)
{
}
CarteDepart::CarteDepart(Face recto, Face verso)
    : Carte(std::move(recto), std::move(verso))
{
}
