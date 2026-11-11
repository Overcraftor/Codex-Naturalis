#pragma once
#include <stack>
#include <vector>

class CartePiochable;
class CarteRessource;
class CarteDorure;

class Pioche
{
protected:
    std::vector<const CartePiochable*> reserve;
    std::vector<const CartePiochable*> visibles;


    void remplirMarche();

public:
    explicit Pioche(std::vector<const CartePiochable*> cartesInitiales);
    virtual ~Pioche() = default;

    const CartePiochable* piocher(int index);

    bool estVide() const;
    int getNbReserve() const;
    const std::vector<const CartePiochable*>& getVisibles() const;
};

class PiocheRessource : public Pioche {
    explicit PiocheRessource(std::vector<const CartePiochable*> cartesInitiales);
};

class PiocheDorure : public Pioche {
    explicit PiocheDorure(std::vector<const CartePiochable*> cartesInitiales);
};
