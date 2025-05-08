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
    const int maxAttempts;
    bool retryAfterFailure = false;
    int scoreGame = 0;
public:
    Game(const std::string& raspuns,
         const std::vector<std::unique_ptr<WordValidator>>& val,
         const int& incercari_max);
    Game(const Game& other); // constr copiere
    Game& operator=(Game other); // copy and swap
    void play();
    static int score(const int &currentAttempt, const int &maxAttempts, const int &difficultyMultiplier);
    static void printRemainingAttempts(const int &currentAttempt, const int &maxAttempts);
    static std::unique_ptr<FeedbackStrategy> alegeModFeedback();
    void printValidatorTypes() const;
    static const int SCORE_MULTIPLIER;
};

#endif //GAME_H
