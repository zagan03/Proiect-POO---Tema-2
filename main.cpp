#include "LengthValidator.h"
#include "WordValidator.h"
#include "AlphabetValidator.h"
#include "ClassicFeedback.h"
#include "FeedbackStrategy.h"
#include "Game.h"
#include "DictionaryValidator.h"
#include <iostream>
#include "ValidatorExceptions.h"





int main()
{
    try
    {
        std::vector<std::unique_ptr<WordValidator>> validators;

        // Adaugam validatorii
        validators.emplace_back(std::make_unique<LengthValidator>(5));
        validators.emplace_back(std::make_unique<AlphabetValidator>());

        // Verificam daca fisierul tastatura.txt se deschide
        std::unique_ptr<DictionaryValidator> dict = std::make_unique<DictionaryValidator>("tastatura.txt");
        // aici in cazul in care fisierul nu se deschide, se 'arunca' exceptia din constructorul validatorului
        std::string chosenWord = dict->getRandomWord();
        // validam cuvantul ce trebuie ghicit, in cazul in care nu are cinci litere, aruncam exceptie
        if (chosenWord.length() != 5)
            throw ValidatorExceptions("Cuvantul din dictionar nu are 5 litere!" + chosenWord);
        validators.emplace_back(dict->clone());
        if (validators.empty())
            throw ValidatorExceptions("Lista de validatori este goala. Nu putemm continua jocul");

        Game Joc(chosenWord, validators, 6);

        // Folosit pentru a arata utilizatorului Regulile in functie de care trebuie alese cuvintele.
        Joc.printValidatorTypes();

        // Rulam jocul
        Joc.play();
    }
    catch (const ValidatorExceptions& e) {
        std::cerr << "Exceptie prinsa in main: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Alta exceptie: " << e.what() << std::endl;
    }
    return 0;
}
