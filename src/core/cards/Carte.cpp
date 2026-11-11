#include "Carte.h"

#include <utility>

Carte::Carte(Face* recto, Face* verso)
    : recto(recto), verso(verso)
{
}

Face& Carte::getRecto() const {
    return *recto;
}

Face& Carte::getVerso() const
{
    return *verso;
}

CartePiochable::CartePiochable(Face* recto, Face* verso, const Resource r)
    : Carte(recto, verso), regne(r)
{
}

Resource CartePiochable::getRegne() const {
    return regne;
}

CarteRessource::CarteRessource(Face* recto, Face* verso, const Resource r)
    : CartePiochable(recto, verso, r)
{
}

CarteDorure::CarteDorure(Face* recto, Face* verso, const Resource r)
    : CartePiochable(recto, verso, r)
{
}
CarteDepart::CarteDepart(Face* recto, Face* verso)
    : Carte(recto, verso)
{
}
