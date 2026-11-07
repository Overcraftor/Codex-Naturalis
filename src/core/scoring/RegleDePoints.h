#pragma once
#include "Types.h"

class Manuscrit;
struct Placement;

class RegleDePoints {
protected:
    int valeur;

public:
    explicit RegleDePoints(const int val) : valeur(val) {}
    virtual ~RegleDePoints() = default;

    virtual int calculer(const Manuscrit& m, const Placement& p) const = 0; // doit être rédéfinie

    int getValeur() const { return valeur; }
};


class PointsFixes : public RegleDePoints {
public:
    explicit PointsFixes(const int val) : RegleDePoints(val) {}

    int calculer(const Manuscrit& m, const Placement& p) const override;
};

class PointsParObjet : public RegleDePoints {
    Object objetCible;

public:
    PointsParObjet(const int val, const Object obj) : RegleDePoints(val), objetCible(obj) {}
    int calculer(const Manuscrit& m, const Placement& p) const override;
};

class PointsParCoinRecouvert : public RegleDePoints {
public:
    explicit PointsParCoinRecouvert(const int val) : RegleDePoints(val) {}
    int calculer(const Manuscrit& m, const Placement& p) const override;
};