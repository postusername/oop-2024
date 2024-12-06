#pragma once

#include <string>

class ISkill {
public:
    virtual ~ISkill() = default;
    virtual void apply() = 0;
    virtual std::string getName() = 0;
};