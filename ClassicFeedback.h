
#ifndef CLASSICFEEDBACK_H
#define CLASSICFEEDBACK_H
#include "FeedbackStrategy.h"
#include <string>

// Acesta este un feedback ce afiseaza in consola textul colorat in functie de corectitudinea literelor alese.


class ClassicFeedback : public FeedbackStrategy
{
public:
    std::string getFeedback(const std::string &input, const std::string &answer) const override;

    static std::string toLowerCase(const std::string& word);
};

#endif //CLASSICFEEDBACK_H
