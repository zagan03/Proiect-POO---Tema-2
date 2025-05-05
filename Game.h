

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
    Game(const Game& other); // constr copiere
    Game& operator=(Game other); // copy and swap
    void play();
    static int score(const int &currentAttempt, const int &maxAttempts);
    static void printRemainingAttempts(const int &currentAttempt, const int &maxAttempts);
    void printValidatorTypes() const;
private:
    std::string answer;
    std::vector <std::unique_ptr<WordValidator>> validatori;
    int currentAttempt;
    const int maxAttempts;
    bool retryAfterFailure = false;
};

#endif //GAME_H
