#pragma once

#include <string>
#include "../ShipManager.h"
#include "../GameBoard.h"

class ISkill {
public:
    virtual ~ISkill() = default;
    virtual void apply(size_t ax, size_t ay, GameBoard &enemyBoard, ShipManager &enemyShipManager) = 0;
    virtual std::string getName() = 0;
};