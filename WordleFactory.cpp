#include "WordleFactory.h"
#include "LengthValidator.h"
#include "AlphabetValidator.h"
#include "DictionaryValidator.h"
#include "ValidatorExceptions.h"

#include <unordered_set>
#include <memory>

Game& WordleFactory::createDefaultGame(const std::string& filename) {
    std::vector<std::unique_ptr<WordValidator>> validators;

    // adugam alphabet si length validator
    validators.emplace_back(std::make_unique<LengthValidator>(5));

    std::unordered_set<char> charset;
    for (char c = 'a'; c <= 'z'; ++c)
        charset.insert(c);
    validators.emplace_back(std::make_unique<AlphabetValidator<std::unordered_set<char>>>(charset));

    // DictionaryValidator
    std::unique_ptr<DictionaryValidator> dict = std::make_unique<DictionaryValidator>(filename);
    std::string word = dict->getRandomWord();

    if (word.length() != 5)
        throw ValidatorExceptions("Cuvântul ales nu are 5 litere: " + word);
    if (validators.empty())
        throw ValidatorExceptions("Lista de validatori este goala. Nu putem continua jocul");
    validators.emplace_back(dict->clone());
    return Game::getInstance(word, validators, 6);
}
