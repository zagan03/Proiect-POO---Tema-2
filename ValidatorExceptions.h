#ifndef VALIDATOREXCEPTIONS_H
#define VALIDATOREXCEPTIONS_H

class ValidatorExceptions: public std::exception
{
    std::string message;
public:
    explicit ValidatorExceptions(const std::string &msg): message(msg) {}
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

class AlphabetValidatorException: public ValidatorExceptions
{
public:
    explicit AlphabetValidatorException(const std::string &msg): ValidatorExceptions(msg) {}
};

class LengthValidatorException: public ValidatorExceptions
{
public:
    explicit LengthValidatorException(const std::string &msg): ValidatorExceptions(msg) {}
};

class DictionaryValidatorException: public ValidatorExceptions
{
public:
    explicit DictionaryValidatorException(const std::string &msg): ValidatorExceptions(msg) {}
};

class EmptyDictionaryException : public ValidatorExceptions
{
public:
    explicit EmptyDictionaryException(const std::string& msg) : ValidatorExceptions(msg) {}
};

#endif //VALIDATOREXCEPTIONS_H
