#include "DoubleDamageFactory.h"

ISkill *DoubleDamageFactory::createAbility(InputProcessor &inputProcessor, GameBoard &aiBoard, ShipManager &aiShipManager) {
    return new DoubleDamage(inputProcessor);
}
