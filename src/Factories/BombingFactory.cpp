#include "BombingFactory.h"

ISkill* BombingFactory::createAbility(GameBoard &aiBoard, ShipManager &aiShipManager) {
    return new Bombing(aiShipManager);
}