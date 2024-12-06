#include "SkillException.h"

const char* SkillException::what() const noexcept {
    return "Error in using the ability!";
}

const char* NoAbilitiesAvailableException::what() const noexcept {
    return "No abilities available!";
}

const char* InvalidAbilityCoordsException::what() const noexcept {
    return "Invalid ability coordinates!";
}
