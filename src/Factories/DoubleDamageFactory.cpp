#include "DoubleDamageFactory.h"


ISkill *DoubleDamageFactory::createAbility(GameBoard &aiBoard, ShipManager &aiShipManager) {
    return new DoubleDamage();
}
