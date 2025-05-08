#include "NoFeedback.h"
#include <iostream>
#include <algorithm>

    std::string NoFeedback::toLowerCase(const std::string& word)
    {
        std::string result = word;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    std::string NoFeedback::getFeedback(const std::string& input, const std::string& answer) const
    {
        (void)input; // pentru a evita warning-ul de not used variable
        (void)answer; // la fel ca mai sus
        std::cout << "[Feedback dezactivat pentru acest mod.]\n";
        return "";
    }
