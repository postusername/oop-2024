#include "ScannerFactory.h"

ISkill* ScannerFactory::createAbility(GameBoard &enemyBoard, ShipManager &enemyShipManager) {
    return new Scanner(enemyBoard);
}
