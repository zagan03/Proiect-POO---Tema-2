

#ifndef GAME_H
#define GAME_H
#include "WordValidator.h"
#include <vector>
#include <memory>

class Game
{
public:
    Game(const std::string& raspuns,
         const std::vector<std::unique_ptr<WordValidator>>& val,
         const int& incercari_max);
    void play();
    static int score(const int &currentAttempt, const int &maxAttempts);
    static void printRemainingAttempts(const int &currentAttempt, const int &maxAttempts);
private:
    std::string answer;
    std::vector <std::unique_ptr<WordValidator>> validatori;
    int currentAttempt;
    const int maxAttempts;
};

#endif //GAME_H
