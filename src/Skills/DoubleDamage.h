#pragma once

#include "ISkill.h"

class DoubleDamage : public ISkill {
private:
public:
    DoubleDamage();
    void apply(size_t ax, size_t ay) override;
    std::string getName() override;
};