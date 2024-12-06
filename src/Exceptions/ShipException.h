#pragma once

#include <exception>

class ShipException : public std::exception {
public:
    const char* what() const noexcept override;
};

class ShipPlacementException : public ShipException {
public:
    const char* what() const noexcept override;
};

class ShipOutOfBoundsException : public ShipPlacementException {
public:
    const char* what() const noexcept override;
};

class ShipOverlapsException : public ShipPlacementException {
public:
    const char* what() const noexcept override;
};