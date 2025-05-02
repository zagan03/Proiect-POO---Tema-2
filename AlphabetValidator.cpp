#include "WordValidator.h"
#include "AlphabetValidator.h"
#include "ValidatorExceptions.h"
#include <iostream>
#include <cctype> // pt isalpha
#include <memory>



bool AlphabetValidator::validate(const std::string &word) const
{
    for (char c : word)
        {
        if (!std::isalpha(static_cast<unsigned char>(c)))
            {
        return false;
            }
        }
    return true;
}

// functie folosita pentru exceptii
void AlphabetValidator::throwExc(const std::string &word) const
{
        if (!validate(word))
        {
            throw AlphabetValidatorException("Cuvantul trebuie sa contina doar litere.");
        }
}

std::unique_ptr<WordValidator> AlphabetValidator::clone() const
{
    return std::make_unique<AlphabetValidator>(*this);
}

void AlphabetValidator::printDetails() const
{
    std::cout << "Permite doar litere din alfabetul englez (a - z, A-Z).\n";
}

std::ostream& operator<<(std::ostream& os, const AlphabetValidator& av) {
    os << "AlphabetValidator: permite doar litere din alfabetul englez." << std::endl;
    return os;
}

