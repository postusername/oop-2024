#include "ScannerFactory.h"

ISkill* ScannerFactory::createAbility(InputProcessor &inputProcessor, GameBoard &enemyBoard, ShipManager &enemyShipManager) {
    return new Scanner(enemyBoard, inputProcessor);
}
