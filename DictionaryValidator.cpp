#include "DictionaryValidator.h"
#include "ValidatorExceptions.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>

// constructor initializare
DictionaryValidator::DictionaryValidator(const std::string &filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw DictionaryValidatorException("Nu s-a putut deschide fisierul: " + filename);
    }

    std::string line;
    while (std::getline(file,line))
    {
        if (!line.empty())
        {
         dictionary.push_back(line);
        }
    }

    if (dictionary.empty())
    {
        throw EmptyDictionaryException("Fisierul " + filename + " nu contine cuvinte valide.");
    }
}


    DictionaryValidator::DictionaryValidator(const DictionaryValidator& other) : dictionary(other.dictionary) {}
    // Operator copy and swap
    DictionaryValidator& DictionaryValidator::operator=(DictionaryValidator other)
    {
    std::swap(dictionary, other.dictionary);
    return *this;
    }

bool DictionaryValidator::validate (const std::string &word) const
{
    if (std::find(dictionary.begin(), dictionary.end(), word) == dictionary.end())
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
    std::cout << "Valideaza folosind " << dictionary.size() << " cuvinte din dictionar.\n";
}

// Functie generare cuvant random
std::string DictionaryValidator::getRandomWord() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,dictionary.size()-1);
    return dictionary[dist(gen)];
}

std::ostream& operator<<(std::ostream& os, const DictionaryValidator& dv)
{
    os << "DictionaryValidator: Dictionarul are " << dv.getWordCount() << " cuvinte." << std::endl;
    return os;
}

int DictionaryValidator::getWordCount() const
{
    return dictionary.size();
}

