#include "DictionaryValidator.h"
#include "ValidatorExceptions.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>

// constructor initializare
DictionaryValidator::DictionaryValidator(const std::string &filename)
{
    std::ifstream fisier(filename);

    if (!fisier.is_open())
    {
        throw DictionaryValidatorException("Nu s-a putut deschide fisierul: " + filename);
    }

    std::string line;
    while (std::getline(fisier,line))
    {
        if (!line.empty())
        {
         dictionar.push_back(line);
        }
    }

    if (dictionar.empty())
    {
        throw EmptyDictionaryException("Fisierul " + filename + " nu contine cuvinte valide.");
    }
}


    DictionaryValidator::DictionaryValidator(const DictionaryValidator& other) : dictionar(other.dictionar) {}
    // Operator copy and swap
    DictionaryValidator& DictionaryValidator::operator=(DictionaryValidator other)
    {
    std::swap(dictionar, other.dictionar);
    return *this;
    }

bool DictionaryValidator::validate (const std::string &word) const
{
    if (std::find(dictionar.begin(), dictionar.end(), word) == dictionar.end())
    {
        return false;
    }
    return true;
}

void DictionaryValidator::throwExc(const std::string &word) const
{
    if (!validate(word))
    {
        throw DictionaryValidatorException("Cuvantul nu exista in dictionar.");
    }
}



std::unique_ptr<WordValidator> DictionaryValidator::clone() const
{
    return std::make_unique<DictionaryValidator>(*this);
}

void DictionaryValidator::printDetails() const
{
    std::cout << "Valideaza folosind " << dictionar.size() << " cuvinte din dictionar.\n";
}

// Functie generare cuvant random
std::string DictionaryValidator::getRandomWord() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,dictionar.size()-1);
    return dictionar[dist(gen)];
}

std::ostream& operator<<(std::ostream& os, const DictionaryValidator& dv)
{
    os << "DictionaryValidator: Dictionarul are " << dv.getWordCount() << " cuvinte." << std::endl;
    return os;
}

size_t DictionaryValidator::getWordCount() const
{
    return dictionar.size();
}

