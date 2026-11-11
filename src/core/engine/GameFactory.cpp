#include "GameFactory.h"

#include <fstream>

#include "Types.h"
#include "cards/Carte.h"
#include "cards/Face.h"
#include <nlohmann/json.hpp>

#include "scoring/RegleDePoints.h"
using nlohmann::json;

static Coin creerCoin(const PositionCoin pos, const std::string& value) {
    if (value == "INVISIBLE") return {pos, false};
    if (value == "VIDE")      return {pos, true};

    if (value == "CHAMPIGNON") return {pos, true, Resource::CHAMPIGNON, std::nullopt};
    if (value == "VEGETAL")    return {pos, true, Resource::VEGETAL, std::nullopt};
    if (value == "ANIMAL")     return {pos, true, Resource::ANIMAL, std::nullopt};
    if (value == "INSECTE")    return {pos, true, Resource::INSECTE, std::nullopt};

    if (value == "PLUME")     return {pos, true, std::nullopt, Object::PLUME};
    if (value == "ENCRIER")   return {pos, true, std::nullopt, Object::ENCRIER};
    if (value == "PARCHEMIN") return {pos, true, std::nullopt, Object::PARCHEMIN};

    return {pos, false};
}

static Resource stringToResource(const std::string& value)
{
    if (value == "CHAMPIGNON") return Resource::CHAMPIGNON;
    if (value == "VEGETAL") return Resource::VEGETAL;
    if (value == "ANIMAL") return Resource::ANIMAL;
    if (value == "INSECTE") return Resource::INSECTE;
    if (value == "AUCUNE") return Resource::AUCUNE;
    throw std::invalid_argument("Ressource inconnue : " + value);
}

static Object stringToObjet(const std::string& str) {
    if (str == "PLUME") return Object::PLUME;
    if (str == "ENCRIER") return Object::ENCRIER;
    if (str == "PARCHEMIN") return Object::PARCHEMIN;
    throw std::invalid_argument("Objet inconnu : " + str);
}

std::vector<std::shared_ptr<const CartePiochable>> GameFactory::genererCartesRessources()
{
    std::vector<std::shared_ptr<const CartePiochable>> cartes;
    cartes.reserve(40);

    std::ifstream file(CARTES_RESSOURCES_FILE);
    if (!file.is_open())
        throw std::runtime_error("Impossible de trouver le fichier des cartes ressources");
    json data = json::parse(file);

    // VERSO (4 coins vide pour toutes les cartes)
    const std::array<Coin, 4> coinsVerso = {
        Coin(PositionCoin::HG, true),
        Coin(PositionCoin::HD, true),
        Coin(PositionCoin::BG, true),
        Coin(PositionCoin::BD, true)
    };

    for (const auto& item : data)
    {
        const Resource regne = stringToResource(item["regne"]);

        // recto
        const std::array<Coin, 4> coinsRecto = {
            creerCoin(PositionCoin::BD, item["recto"]["BD"]),
            creerCoin(PositionCoin::BG, item["recto"]["BG"]),
            creerCoin(PositionCoin::HD, item["recto"]["HD"]),
            creerCoin(PositionCoin::HG, item["recto"]["HG"])
        };

        std::shared_ptr<RegleDePoints> regle = nullptr;
        if (item.contains("points") && item["points"] > 0)
            regle = std::make_shared<PointsFixes>(item["points"]);

        const Face recto = Face(coinsRecto, {}, {}, regle);
        const Face verso = Face(coinsVerso, {regne}, {});

        cartes.push_back(std::make_shared<CarteRessource>(recto, verso, regne));
    }

    return cartes;
}

std::vector<std::shared_ptr<const CartePiochable>> GameFactory::genererCartesDorures()
{
    std::vector<std::shared_ptr<const CartePiochable>> cartes;
    cartes.reserve(40);

    std::ifstream file(CARTES_DORURES_FILE);
    if (!file.is_open())
        throw std::runtime_error("Impossible de trouver le fichier des cartes dorures");
    json data = json::parse(file);

    // VERSO (4 coins vide pour toutes les cartes)
    const std::array<Coin, 4> coinsVerso = {
        Coin(PositionCoin::HG, true),
        Coin(PositionCoin::HD, true),
        Coin(PositionCoin::BG, true),
        Coin(PositionCoin::BD, true)
    };

    for (const auto& item : data)
    {
        const Resource regne = stringToResource(item["regne"]);

        // recto
        const std::array<Coin, 4> coinsRecto = {
            creerCoin(PositionCoin::BD, item["recto"]["BD"]),
            creerCoin(PositionCoin::BG, item["recto"]["BG"]),
            creerCoin(PositionCoin::HD, item["recto"]["HD"]),
            creerCoin(PositionCoin::HG, item["recto"]["HG"])
        };

        // cost
        std::vector<Resource> coutRecto;
        if (item.contains("cout"))
        {
            for (const auto& [resource, quantity] : item["cout"].items())
            {
                Resource r = stringToResource(resource);
                for (int i = 0; i < quantity; ++i) {
                    coutRecto.push_back(r);
                }
            }
        }

        // points
        std::shared_ptr<RegleDePoints> regle = nullptr;
        if (item.contains("points"))
        {
            std::string type = item["points"]["type"];
            int val = item["points"]["valeur"];

            if (type=="FIXE")
            {
                regle = std::make_shared<PointsFixes>(val);
            } else if (type=="PAR_OBJET")
            {
                Object object = stringToObjet(item["points"]["objet"]);
                regle = std::make_shared<PointsParObjet>(val, object);
            } else if (type=="PAR_COIN")
            {
                regle = std::make_shared<PointsParCoinRecouvert>(val);
            }
        }

        const Face recto = Face(coinsRecto, {}, coutRecto, regle);
        const Face verso = Face(coinsVerso, {regne}, {});

        cartes.push_back(std::make_shared<CarteRessource>(recto, verso, regne));
    }

    return cartes;
}

std::vector<std::shared_ptr<const CarteDepart>> GameFactory::genererCartesDepart()
{
    std::vector<std::shared_ptr<const CarteDepart>> cartes;
    cartes.reserve(6);

    std::ifstream file(CARTES_DEPART_FILE);
    if (!file.is_open())
        throw std::runtime_error("Erreur : Impossible de trouver assets/cartes_depart.json");
    json data = json::parse(file);

    for (const auto& item : data) {
        std::array<Coin, 4> coinsRecto = {
            creerCoin(PositionCoin::HG, item["recto"]["HG"]),
            creerCoin(PositionCoin::HD, item["recto"]["HD"]),
            creerCoin(PositionCoin::BG, item["recto"]["BG"]),
            creerCoin(PositionCoin::BD, item["recto"]["BD"])
        };
        Face recto(coinsRecto, {}, {}, nullptr);

        std::array<Coin, 4> coinsVerso = {
            creerCoin(PositionCoin::HG, item["verso"]["HG"]),
            creerCoin(PositionCoin::HD, item["verso"]["HD"]),
            creerCoin(PositionCoin::BG, item["verso"]["BG"]),
            creerCoin(PositionCoin::BD, item["verso"]["BD"])
        };

        std::vector<Resource> centreVerso;
        if (item["verso"].contains("centre")) {
            for (const auto& resString : item["verso"]["centre"]) {
                centreVerso.push_back(stringToResource(resString.get<std::string>()));
            }
        }

        Face verso(coinsVerso, centreVerso, {}, nullptr);

        cartes.push_back(std::make_shared<CarteDepart>(recto, verso));
    }

    return cartes;
}

std::vector<std::shared_ptr<const Objectif>> GameFactory::genererObjectifs()
{
    // TODO
}
