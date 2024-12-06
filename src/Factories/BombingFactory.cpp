#include "BombingFactory.h"

ISkill* BombingFactory::createAbility(InputProcessor &inputProcessor, GameBoard &aiBoard, ShipManager &aiShipManager) {
    return new Bombing(aiShipManager);
}