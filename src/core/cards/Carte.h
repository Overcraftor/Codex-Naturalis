#pragma once

#include "Face.h"

class Carte {
    Face* recto;
    Face* verso;

protected:
    Carte(Face* recto, Face* verso);

public:
    virtual ~Carte()
    {
        delete recto;
        delete verso;
    };

    Carte(const Carte&) = delete;
    Carte& operator=(const Carte&) = delete;

    // getters
    Face& getRecto() const;
    Face& getVerso() const;
};


class CartePiochable : public Carte {
    Resource regne;

protected:
    CartePiochable(Face* recto, Face* verso, Resource r);

public:
    ~CartePiochable() override = default;

    // getters
    Resource getRegne() const;
};


class CarteRessource : public CartePiochable {
public:
    CarteRessource(Face* recto, Face* verso, Resource r);
    ~CarteRessource() override = default;
};


class CarteDorure : public CartePiochable {
public:
    CarteDorure(Face* recto, Face* verso, Resource r);
    ~CarteDorure() override = default;
};

class CarteDepart : public Carte {
public:
    CarteDepart(Face* recto, Face* verso);
    ~CarteDepart() override = default;
};