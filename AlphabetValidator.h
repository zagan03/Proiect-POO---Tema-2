#ifndef ALPHABETVALIDATOR_H
#define ALPHABETVALIDATOR_H

#include "WordValidator.h"
#include "ValidatorExceptions.h"
#include <iostream>
#include <unordered_set>
#include <memory>

template <typename T>
class AlphabetValidator : public WordValidator {
    T allowedCharacters; // in exemplul din main, T va fi un unordered_set cu toate caracterele de la a la z,
                         // dar ar putea fi si std::vector, etc.
public:
    AlphabetValidator(T allowedChars);
    AlphabetValidator(const AlphabetValidator<T>& other);
    AlphabetValidator<T>& operator=(AlphabetValidator<T> other); // operator =

    std::unique_ptr<WordValidator> clone() const override;
    bool validate(const std::string& word) const override;
    void throwExc(const std::string& word) const override;
    void printDetails() const override;

    bool isCharAllowed(char c) const; // functie care verifica daca o litera este permisa

    ~AlphabetValidator() override {}

    template <typename U> // functie friend cu operator "<<" pentru a afisa regulile de joc utilizatorului
    friend std::ostream& operator<<(std::ostream& os, const AlphabetValidator<U>& av);
};

#endif // ALPHABETVALIDATOR_H
