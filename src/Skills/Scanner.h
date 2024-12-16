#pragma once

#include "ISkill.h"
#include "../GameBoard.h"
#include "../Exceptions/SkillException.h"

class Scanner : public ISkill {
private:
    GameBoard& enemyBoard;
public:
    Scanner(GameBoard& enemyBoard);
    void apply(size_t ax, size_t ay) override;
    std::string getName() override;
};
