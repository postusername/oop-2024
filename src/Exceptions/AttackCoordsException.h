#pragma once

#include <exception>

class AttackCoordsException : public std::exception {
public:
    const char* what() const noexcept override;
};