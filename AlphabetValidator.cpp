#include "WordValidator.h"
#include "AlphabetValidator.h"
#include "ValidatorExceptions.h"
#include <iostream>
#include <memory>

template <typename T>
AlphabetValidator<T>::AlphabetValidator(T allowedChars) : allowedCharacters(std::move(allowedChars)) {}

// Copy constructor
template <typename T>
AlphabetValidator<T>::AlphabetValidator(const AlphabetValidator<T>& other)
    : allowedCharacters(other.allowedCharacters) {}

// Operator assignment
template <typename T>
AlphabetValidator<T>& AlphabetValidator<T>::operator=(AlphabetValidator<T> other) {
    std::swap(allowedCharacters, other.allowedCharacters);
    return *this;
}

// clone
template <typename T>
std::unique_ptr<WordValidator> AlphabetValidator<T>::clone() const {
    return std::make_unique<AlphabetValidator<T>>(*this); // doar am adaugat <T>
}

// verifica daca un caracter este permis
template <typename T>
bool AlphabetValidator<T>::isCharAllowed(char c) const {
    return allowedCharacters.find(c) != allowedCharacters.end();
}

// validate
template <typename T>
bool AlphabetValidator<T>::validate(const std::string& word) const {
    for (char c : word) {
        if (!isCharAllowed(c)) {
            return false;
        }
    }
    return true;
}

// Throw exception
template <typename T>
void AlphabetValidator<T>::throwExc(const std::string& word) const {
    if (!validate(word)) {
        throw AlphabetValidatorException("Cuvantul contine caractere nepermise.");
    }
}

// Print
template <typename T>
void AlphabetValidator<T>::printDetails() const {
    std::cout << "Permite doar caracterele: ";
    for (char c : allowedCharacters)
        std::cout << c << ' ';
    std::cout << '\n';
}

// Operator <<
template <typename U>
std::ostream& operator<<(std::ostream& os, const AlphabetValidator<U>& av) {
    os << "AlphabetValidator cu caractere permise: ";
    for (char c : av.allowedCharacters)
        os << c << ' ';
    return os;
}

// instantiere explicita (exemplu cu unordered_set)
template class AlphabetValidator<std::unordered_set<char>>;
template std::ostream& operator<< <std::unordered_set<char>>(std::ostream&, const AlphabetValidator<std::unordered_set<char>>&);
