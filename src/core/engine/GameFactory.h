#pragma once

#include <memory>
#include <vector>

constexpr char CARTES_RESSOURCES_FILE[32] = "assets/cartes_ressources.json";
constexpr char CARTES_DORURES_FILE[32] = "assets/cartes_dorures.json";
constexpr char CARTES_DEPART_FILE[32] = "assets/cartes_depart.json";

class CarteDepart;
class Objectif;
class CartePiochable;

class GameFactory {
public:
    GameFactory() = delete;
    GameFactory& operator=(GameFactory& other) = delete;
    ~GameFactory() = delete;

    // utilisation des shared pointeurs pour ne pas avoir à libérer la mémoire plus tard (c'est automatique)
    static std::vector<std::shared_ptr<const CartePiochable>> genererCartesRessources();
    static std::vector<std::shared_ptr<const CartePiochable>> genererCartesDorures();
    static std::vector<std::shared_ptr<const CarteDepart>> genererCartesDepart();

    static std::vector<std::shared_ptr<const Objectif>> genererObjectifs();
};