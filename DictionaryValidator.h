//
// Created by zagan on 4/24/2025.
//

#ifndef DICTIONARYVALIDATOR_H
#define DICTIONARYVALIDATOR_H

#include "WordValidator.h"
#include <string>
#include <memory>
#include <vector>
#include <fstream>

class DictionaryValidator: public WordValidator
{
private:
    std::vector<std::string> dictionary;
public:
    DictionaryValidator(const std::string& filename);
    DictionaryValidator(const DictionaryValidator& other);
    DictionaryValidator& operator=(DictionaryValidator other);

    std::unique_ptr<WordValidator> clone() const override;
    bool validate(const std::string& word) const override;
    void throwExc(const std::string &word) const override;
    void printDetails() const override;
    friend std::ostream& operator<<(std::ostream& os,const DictionaryValidator& dv);
    int getWordCount() const;
    std::string getRandomWord () const ;

    ~DictionaryValidator() override {}
};
#endif //DICTIONARYVALIDATOR_H
