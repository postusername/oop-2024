#pragma once

#include "ISkill.h"
#include "../IO/InputProcessor.h"

class DoubleDamage : public ISkill {
private:
    InputProcessor& inputProcessor;
public:
    DoubleDamage(InputProcessor& inputProcessor);
    void apply() override;
    std::string getName() override;
};