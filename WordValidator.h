
#ifndef WORDVALIDATOR_H
#define WORDVALIDATOR_H

#include <cstring>
#include <iostream>
#include <string>
#include <memory>

class WordValidator
{
public:
    virtual bool validate (const std::string &cuvant) const = 0;
    virtual std::unique_ptr<WordValidator> clone() const = 0;  // pointer care sterge automat obiectul cand
                                                               // nu mai este utilizat si se asigura ca
                                                               // exista un singur owner pt un obiect
    virtual void throwExc(const std::string &word) const = 0;
    void functiePrintare() const;
    virtual void printDetails() const = 0;
    ~WordValidator() = default;
};





#endif //WORDVALIDATOR_H
