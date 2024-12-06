#include "ShipException.h"

const char* ShipException::what() const noexcept {
    return "Error in using the ship!";
}

const char* ShipPlacementException::what() const noexcept {
    return "Incorrect ship placement, try again!";
}

const char* ShipOutOfBoundsException::what() const noexcept {
    return "The ship's coordinates are out of bounds, try again!";
}

const char* ShipOverlapsException::what() const noexcept {
    return "A ship is overlaps another ship, try again!";
}
