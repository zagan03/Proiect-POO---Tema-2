#ifndef GAME_H
#define GAME_H
#include "WordValidator.h"
#include "FeedbackStrategy.h"
#include <vector>
#include <memory>

class Game
{
private:
    std::string answer;
    std::vector <std::unique_ptr<WordValidator>> validatori;
    int currentAttempt;
    int maxAttempts;
    int scoreGame = 0;
    static std::unique_ptr<Game> instance;

    // constructor privat
    Game(const std::string& raspuns,
     const std::vector<std::unique_ptr<WordValidator>>& val,
     const int& incercari_max);
    // interzicem copiere/atribuire
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
public:
    // metoda pentru a obtine instanta unica
    static Game& getInstance(const std::string& raspuns,
                             const std::vector<std::unique_ptr<WordValidator>>& val,
                             const int& incercari_max);
    void play();
    static int score(const int &currentAttempt, const int &maxAttempts, const int &difficultyMultiplier);
    static void printRemainingAttempts(const int &currentAttempt, const int &maxAttempts);
    static std::unique_ptr<FeedbackStrategy> alegeModFeedback();
    void printValidatorTypes() const;
    static const int SCORE_MULTIPLIER;
    void addExtraAttempt();
};

#endif //GAME_H
