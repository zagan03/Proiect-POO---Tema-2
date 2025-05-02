#include "Game.h"
#include <vector>
#include <memory>

#include "ValidatorExceptions.h"
#include "ClassicFeedback.h"
#include "FeedbackStrategy.h"

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
                std::cout << "Scorul dvs. : " << score(currentAttempt,maxAttempts) << std::endl;
                break;
            }
            else if (input != answer && currentAttempt == maxAttempts - 1)
            {
                std::cout << "Ne pare rau! Nu ati ghicit Cuvantul. Cuvantul era: " << answer << std::endl;
                currentAttempt++;
                std::cout << "Scorul dvs. : " << score(currentAttempt,maxAttempts);
                break;
            }
            currentAttempt++;
            std::cout << "Scorul tau este: " << score(currentAttempt, maxAttempts) << std::endl;
        }
        catch (const LengthValidatorException& e) {
            std::cout << "Lungimea cuvantului este gresita: " << e.what() << "\n";
        }
        catch (const AlphabetValidatorException& e) {
            std::cout << "Cuvantul contine caractere nepermise: " << e.what() << "\n";
        }
        catch (const DictionaryValidatorException& e) {
            std::cout << "Eroare de validare: " << e.what() << "\n";
        }
    }
}



