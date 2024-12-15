#pragma once

#include "ISkill.h"
#include "../IO/InputProcessor.h"

class DoubleDamage : public ISkill {
private:
public:
    DoubleDamage();
    void apply() override;
    std::string getName() override;
};