#include "WordValidator.h"
#include "LengthValidator.h"
#include "ValidatorExceptions.h"
#include <iostream>
#include <vector>
#include <memory>

    int LengthValidator::defaultLength = 5;
    LengthValidator::LengthValidator(const unsigned int len): requiredLength(len) {} // dimensiune automata de 5

    bool LengthValidator::validate(const std::string &cuvant) const
    {
        return (requiredLength == cuvant.size());
    }

    void LengthValidator::throwExc(const std::string &word) const
    {
        if (!validate(word))
        {
            throw LengthValidatorException("Cuvantul trebuie sa aiba exact 5 litere.");
        }
    }


    std::unique_ptr<WordValidator> LengthValidator::clone() const
    {
        return std::make_unique<LengthValidator>(*this);// creeaza o copie a obiectului *this, si returneaza un pointer catre obiect
    }

    // Constructor copiere
    LengthValidator::LengthValidator(const LengthValidator& other) : requiredLength(other.requiredLength) {}

    // Operator Copy and swap
    LengthValidator& LengthValidator::operator=(LengthValidator other)
    {
        std::swap(requiredLength, other.requiredLength);
        return *this;
    }

    void LengthValidator::printDetails() const
    {
        std::cout << "Lungime fixa permisa: 5 caractere.\n";
    }

    std::ostream& operator<<(std::ostream& os, const LengthValidator& lv)
    {
        os << "LengthValidator cu lungime: " << lv.requiredLength << std::endl;
        return os;
    }


