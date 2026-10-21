//
// Created by catal on 4/27/2026.
//

#ifndef A6_7_EXCEPTIONS_H
#define A6_7_EXCEPTIONS_H
#include <exception>
#include <stdexcept>
#include "../domain/domain.h"
/**
 *Exceptions for the repository
 *Exceptions for the input
 *Validate entities using validators
 *(validate a pet) - CHECK Lecture7 demo SpaceshipValidator:: validate();
 *
 **/
#include <string>

class RepositoryException : public std::runtime_error {
public:
    explicit RepositoryException(const std::string &message)
        : std::runtime_error(message) {
    }
};

class FileException : public std::runtime_error {
public:
    explicit FileException(const std::string &message)
        : std::runtime_error(message) {
    }
};

class UpdateException : public std::runtime_error {
public:
    explicit UpdateException(const std::string &message)
        : std::runtime_error("Failed to update " + message) {
    }

};
class InvalidChoiceException : public std::runtime_error {
    public:
    explicit InvalidChoiceException() : std::runtime_error("Invalid choice!") {}
};

class PetValidator {
public:
    static void validate(const Pet &p);


};
class ValidationException : public std::runtime_error
{
public:
    explicit ValidationException(std::string message)
        : std::runtime_error(message) {}
};
class ListException : public std::runtime_error {
    public:
    explicit ListException(std::string message)
        : std::runtime_error(message) {}
};
#endif //A6_7_EXCEPTIONS_H
