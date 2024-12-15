#pragma once

#include "ISkill.h"
#include "../IO/InputProcessor.h"
#include "../GameBoard.h"
#include "../Exceptions/SkillException.h"

class Scanner : public ISkill {
private:
    GameBoard& enemyBoard;
public:
    Scanner(GameBoard& enemyBoard);
    void apply() override;
    std::string getName() override;
};
