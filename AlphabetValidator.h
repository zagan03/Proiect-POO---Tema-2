//
// Created by zagan on 4/21/2025.
//

#ifndef ALPHABETVALIDATOR_H
#define ALPHABETVALIDATOR_H
#include "WordValidator.h"
#include <string>


class AlphabetValidator: public WordValidator
{
public:
        // constructor de initializare implicit
        std::unique_ptr<WordValidator> clone() const override;
        bool validate(const std::string &word) const override;
        void throwExc(const std::string &word) const override;
        void printDetails() const override;
        friend std::ostream& operator<<(std::ostream& os, const AlphabetValidator& av);
        ~AlphabetValidator() {}
};


#endif //ALPHABETVALIDATOR_H
