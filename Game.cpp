#include "Game.h"
#include <vector>
#include <memory>

#include "ValidatorExceptions.h"
#include "ClassicFeedback.h"
#include "FeedbackStrategy.h"
#include "WordValidator.h"
#include "AlphabetValidator.h"
#include "DictionaryValidator.h"
#include "LengthValidator.h"

Game::Game(const std::string& raspuns,
           const std::vector<std::unique_ptr<WordValidator>>& val,
           const int& incercari_max)
    : answer(raspuns),
      currentAttempt(0),
      maxAttempts(incercari_max)
{
    for (const auto& v : val)
        validatori.push_back(v->clone()); // facem o clona a validatorului si o punem in validatori
}

Game::Game(const Game& other)
    : answer(other.answer),
      currentAttempt(other.currentAttempt),
      maxAttempts(other.maxAttempts),
      retryAfterFailure(other.retryAfterFailure)
{
    for (const auto& validator : other.validatori)
        validatori.push_back(validator->clone());
}

Game& Game::operator=(Game other)
{
    std::swap(answer, other.answer);
    std::swap(currentAttempt, other.currentAttempt);
    std::swap(validatori, other.validatori);
    return *this;
}



int Game::score(const int &currentAttempt, const int &maxAttempts)
{
    return (maxAttempts - currentAttempt) * 20;
}

void Game::printRemainingAttempts(const int &currentAttempt, const int &maxAttempts)
{
    std::cout << "Mai ai " << maxAttempts - currentAttempt << " incercari ramase." << std::endl;
}

void Game::play()
{
    std::string input;
    std::unique_ptr<FeedbackStrategy> feedback = std::make_unique<ClassicFeedback>();
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
                if (retryAfterFailure) {
                    std::cout << "Ati ghicit in runda bonus. Scorul este 0.\n";
                    break;
                }
                std::cout << "Scorul dvs. : " << score(currentAttempt,maxAttempts) << std::endl;
                break;
            }
            else if (input != answer && currentAttempt == maxAttempts - 1)
            {
                currentAttempt++;
                std::string raspuns;
                std::cout << "Scorul dvs. : " << score(currentAttempt,maxAttempts) << std::endl;
                std::cout << "Ne pare rau! Nu ati ghicit cuvantul. Mai doriti inca o incercare? " << std::endl;
                std::cout << "Daca nu doriti, scrieti orice pentru a vedea raspunsul." << std::endl;
                std::cin >> raspuns;
                if (raspuns == "da" || raspuns == "DA")
                {
                    // folosit pentru demonstratia utilizarii operatorului copy and swap
                    currentAttempt--;
                    Game Joc2 = *this;
                    Joc2.retryAfterFailure = true;
                    Joc2.play();
                    break;
                }
                else
                {
                    std::cout << "Cuvantul era: " << answer << std::endl;
                    break;
                }
            }
            currentAttempt++;
            std::cout << "Scorul dvs este: am intrat " << score(currentAttempt, maxAttempts) << std::endl;
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
        else if (const auto* alphaValid = dynamic_cast<AlphabetValidator*>(validator.get())) {
            std::cout << "AlphabetValidator\n";
            alphaValid -> printDetails();
        }
        else
            std::cout << "Necunoscut\n";
    }
}




