#pragma once

#include "Face.h"

class Participant {
    std::string nom;
    int score;

private:
    Participant(const std::string& nom) : nom(nom), score(0) {}

public:
    virtual ~Participant() = default;

    // getters
    const std::string& getNom() const { return nom; }
    int getScore() const { return score; }
};


