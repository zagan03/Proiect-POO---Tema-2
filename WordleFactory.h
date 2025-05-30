#ifndef WORDLEFACTORY_H
#define WORDLEFACTORY_H

#include "Game.h"

class WordleFactory {
public:
    // cream o instanta a unui joc
    static Game& createDefaultGame(const std::string& filename = "tastatura.txt");
};

#endif // WORDLEFACTORY_H
