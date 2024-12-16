#pragma once

#include "ISkill.h"
#include "../ShipManager.h"

class Bombing : public ISkill {
private:
    ShipManager& enemyShipManager;
public:
    Bombing(ShipManager& enemyShipManager);
    void apply(size_t ax, size_t ay) override;
    std::string getName() override;
};