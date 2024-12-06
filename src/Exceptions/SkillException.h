#pragma once

#include <exception>

class SkillException : public std::exception {
public:
    const char* what() const noexcept override;
};

class NoAbilitiesAvailableException : public SkillException {
public:
    const char* what() const noexcept override;
};

class InvalidAbilityCoordsException : public SkillException {
public:
    const char* what() const noexcept override;
};