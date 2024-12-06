#include "AttackCoordsException.h"

const char *AttackCoordsException::what() const noexcept
{
    return "Attack coordinates are out of bounds!";
}
