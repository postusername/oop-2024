#pragma once

#include "ISkill.h"
#include "../ShipManager.h"

class Bombing : public ISkill {
private:
    ShipManager& enemyShipManager;
public:
    Bombing(ShipManager& enemyShipManager);
    void apply() override;
    std::string getName() override;
};