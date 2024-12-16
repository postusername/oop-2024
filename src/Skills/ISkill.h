#pragma once

#include <string>

class ISkill {
public:
    virtual ~ISkill() = default;
    virtual void apply(size_t ax, size_t ay) = 0;
    virtual std::string getName() = 0;
};