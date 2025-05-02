#ifndef FEEDBACKSTRATEGY_H
#define FEEDBACKSTRATEGY_H
#include <string>

// Clasa pentru feedback-ul inputului introdus de utilizator.

class FeedbackStrategy
{
public:
    virtual std::string getFeedback(const std::string &input, const std::string &answer) const = 0;
    virtual ~FeedbackStrategy() {}
};


#endif //FEEDBACKSTRATEGY_H
