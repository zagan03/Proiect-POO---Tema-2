#include "Game.h"
#include "ValidatorExceptions.h"
#include "ClassicFeedback.h"
#include "NoFeedback.h"
#include "FeedbackStrategy.h"
#include "WordValidator.h"
#include "AlphabetValidator.h"
#include "DictionaryValidator.h"
#include "LengthValidator.h"
#include <vector>
#include <memory>
// Constanta folosita la calculul scorului
const int Game::SCORE_MULTIPLIER = 20;

// instanta unica pentru singleton
std::unique_ptr<Game> Game::instance = nullptr;

Game& Game::getInstance(const std::string& raspuns,
                        const std::vector<std::unique_ptr<WordValidator>>& val,
                        const int& incercari_max) {
    if (!instance) {
        instance = std::unique_ptr<Game>(new Game(raspuns, val, incercari_max));
    }
    return *instance;
}


// Constructor privat
Game::Game(const std::string& raspuns,
           const std::vector<std::unique_ptr<WordValidator>>& val,
           const int& incercari_max)
        : answer(raspuns), currentAttempt(0), maxAttempts(incercari_max) {
    for (const auto& v : val)
        validatori.push_back(v->clone());
}



// Formula Calcul scor
int Game::score(const int &currentAttempt, const int &maxAttempts, const int &difficultyMultiplier)
{
    return (maxAttempts - currentAttempt) * SCORE_MULTIPLIER * difficultyMultiplier;
}


void Game::printRemainingAttempts(const int &currentAttempt, const int &maxAttempts)
{
    std::cout << "Mai ai " << maxAttempts - currentAttempt << " incercari ramase." << std::endl;
}

std::unique_ptr<FeedbackStrategy> Game::alegeModFeedback() {
    std::string choice;
    std::cout << "Alege Modul de joc:\n";
    std::cout << "1. ClassicFeedback (Usor)\n";
    std::cout << "2. NoFeedback (Very Hard)\n";
    std::cin >> choice;

    if (choice == "1") return std::make_unique<ClassicFeedback>();
    else if (choice == "2") return std::make_unique<NoFeedback>();
    else {
        std::cout << "Optiune invalida. Se selecteaza modul clasic implicit.\n";
        return std::make_unique<ClassicFeedback>();
    }
}


void Game::play() {
    std::cout << answer;
    std::string input;
    std::unique_ptr<FeedbackStrategy> feedback = alegeModFeedback();
    int difficultyMultiplier = 1; // multiplicator pentru scor

    // Daca Feedback-ul este NoFeedback => Putem obtine un scor mai mare
    if (dynamic_cast<NoFeedback*>(feedback.get())) {
        difficultyMultiplier = 2;
    }

    while (currentAttempt < maxAttempts)
    {
        std::cout << "Introdu un cuvant format din 5 litere: \n";
        printRemainingAttempts(currentAttempt,maxAttempts);
        std::cin >> input;
        input = ClassicFeedback::toLowerCase(input);

        // incercam sa validam cuvantul
        try
        {
            // verificam fiecare validator pentru cuvant
            for (const auto& validator : validatori)
        {
                validator->throwExc(input); // Aruncă excepție dacă validarea nu trece
        }

            // Dacă toate validările au trecut, dăm feedback
            feedback->getFeedback(input, answer);

            if (input == answer)
            {
                std::cout << "Felicitari! Ati ghicit cuvantul!" << std::endl;
                if (maxAttempts > 6) {
                    std::cout << "Ati ghicit in runda bonus din " << maxAttempts <<" incercari. Scorul este 0.\n";
                    scoreGame = 0;
                    break;
                }
                scoreGame = score(currentAttempt,maxAttempts,difficultyMultiplier);
                std::cout << "Scorul dvs. : " << scoreGame << std::endl;
                break;
            }
            else if (input != answer && currentAttempt == maxAttempts - 1)
            {
                currentAttempt++;
                std::string ans;
                scoreGame = score(currentAttempt,maxAttempts,difficultyMultiplier);
                std::cout << "Scorul dvs. : " << score(currentAttempt,maxAttempts,difficultyMultiplier) << std::endl;
                std::cout << "Ne pare rau! Nu ati ghicit cuvantul. Mai doriti inca o incercare? (Apasa 'da' pentru inca o incercare) " << std::endl;
                std::cout << "Daca nu doriti, scrieti orice pentru a vedea raspunsul." << std::endl;
                std::cin >> ans;
                if (ans == "da" || ans == "DA")
                {
                    addExtraAttempt();
                    scoreGame = 0;
                    continue;
                }
                else
                {
                    std::cout << "Cuvantul era: " << answer << std::endl;
                    break;
                }
            }
            currentAttempt++;
            scoreGame = score(currentAttempt, maxAttempts,difficultyMultiplier);
            std::cout << "Scorul dvs este: " << scoreGame << std::endl;
        }
        catch (const LengthValidatorException& e)
        {
            std::cout << "Lungimea cuvantului este gresita: " << e.what() << "\n";
        }
        catch (const AlphabetValidatorException& e)
        {
            std::cout << "Cuvantul contine caractere nepermise: " << e.what() << "\n";
        }
        catch (const DictionaryValidatorException& e)
        {
            std::cout << "Eroare de validare: " << e.what() << "\n";
        }
    }
}


// Afisarea regulilor de validare a cuvintelor la inceputul programului.

void Game::printValidatorTypes() const {
    for (const auto& validator : validatori) {
        std::cout << "Validator de tip: ";
        if (const auto* lenValidator = dynamic_cast<LengthValidator*>(validator.get())) {
            std::cout << "LengthValidator\n";
            std::cout << *lenValidator;
        }
        else if (const auto* dictValidator = dynamic_cast<DictionaryValidator*>(validator.get())) {
            std::cout << "DictionaryValidator\n";
            std::cout << *dictValidator;
        }
        else if (const auto* alphaValid = dynamic_cast<AlphabetValidator<std::unordered_set<char>>*>(validator.get()))
        {
            std::cout << "AlphabetValidator\n";
            alphaValid -> printDetails();
        }
        else
            std::cout << "Necunoscut\n";
    }
}

void Game::addExtraAttempt() {
    maxAttempts++;
    std::cout << "Ai primit o incercare bonus! Total incercari: " << maxAttempts << "\n";
}




