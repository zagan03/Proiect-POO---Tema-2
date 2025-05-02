//
// Created by zagan on 4/16/2025.
//

#ifndef LENGTHVALIDATOR_H
#define LENGTHVALIDATOR_H
#include "WordValidator.h"
#include <string>

class LengthValidator : public WordValidator
{
    size_t requiredLength;
    static size_t defaultLength;
public:
    LengthValidator(size_t len = defaultLength);
    LengthValidator(const LengthValidator& other);
    std::unique_ptr<WordValidator> clone() const override;
    LengthValidator& operator=(LengthValidator other);
    bool validate(const std::string& word) const override;
    void throwExc(const std::string& word) const override;
    size_t getLength() const;
    void printDetails() const override;
    friend std::ostream& operator<<(std::ostream& os, const LengthValidator& lv);
    virtual ~LengthValidator() {}
};


#endif //LENGTHVALIDATOR_H
