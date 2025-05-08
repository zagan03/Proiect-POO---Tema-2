#ifndef NOFEEDBACK_H
#define NOFEEDBACK_H
#include "FeedbackStrategy.h"

// Acesta este un feedback care nu ofera utilizatorului niciun indiciu despre cuvant, pentru a spori dificultatea.

class NoFeedback : public FeedbackStrategy {
public:
    std::string getFeedback(const std::string &input, const std::string &answer) const override;
    static std::string toLowerCase(const std::string& word);
};


#endif //NOFEEDBACK_H
