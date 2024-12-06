#include "Scanner.h"

Scanner::Scanner(GameBoard &enemyBoard, InputProcessor &inputProcessor)
    : enemyBoard(enemyBoard), inputProcessor(inputProcessor) {}

void Scanner::apply()
{
    OutputProcessor::showMessage("Scanner ability applied");
    inputProcessor.getFlag(flagType::Scanner) = true;
    auto coords = InputProcessor::readCoords();
    size_t x = coords.first, y = coords.second;
    if (x >= enemyBoard.getWidth() || y >= enemyBoard.getHeight()){
        throw InvalidAbilityCoordsException();
    }
    for(size_t i = x; i < x + 2; i++){
        for(size_t j = y; j < y + 2; j++){
            if(enemyBoard.isShip(j, i)){
                inputProcessor.getFlag(flagType::ShipFound) = true;
                return;
            }
        }
    }
    inputProcessor.getFlag(flagType::ShipFound) = false;
}

std::string Scanner::getName() {
    return "Scanner";
}
