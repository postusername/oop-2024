#pragma once

#include "ISkillFactory.h"
#include "../Skills/Scanner.h"

class ScannerFactory : public ISkillFactory {
public:
    ISkill* createAbility(InputProcessor &inputProcessor, GameBoard &enemyBoard, ShipManager &enemyShipManager) override;
};