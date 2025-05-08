#ifndef LENGTHVALIDATOR_H
#define LENGTHVALIDATOR_H
#include "WordValidator.h"
#include <string>

class LengthValidator : public WordValidator
{
private:
    unsigned int requiredLength;
    static int defaultLength;
public:
    LengthValidator(unsigned int len = defaultLength);
    LengthValidator(const LengthValidator& other);

    std::unique_ptr<WordValidator> clone() const override;
    LengthValidator& operator=(LengthValidator other);
    bool validate(const std::string& word) const override;
    void throwExc(const std::string& word) const override;
    void printDetails() const override;
    friend std::ostream& operator<<(std::ostream& os, const LengthValidator& lv);
    ~LengthValidator() override {}
};


#endif //LENGTHVALIDATOR_H
