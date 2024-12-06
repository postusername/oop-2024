#include "OutputProcessor.h"

void OutputProcessor::showMessage(const std::string &message) {
    std::cout << message << std::endl;
}

void OutputProcessor::drawBoard(GameBoard& board) const {
    std::cout << "   ";
    auto height = board.getHeight();
    auto width = board.getWidth();
    for (size_t j = 0; j < width; ++j) {
        std::cout << std::setw(3) << j + 1;
    }
    std::cout << std::endl;
    std::cout << "   ";
    for (size_t j = 0; j < width; ++j) {
        std::cout << "---";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < height; ++i) {
        std::cout << std::setw(2) << i + 1 << "|";
        for (size_t j = 0; j < width; ++j) {
            char statusSymbol;
            switch (board(j, i).getStatus()) {
                case ViewState::Ship: statusSymbol = '#'; break;
                case ViewState::Destroyed: statusSymbol = 'X'; break;
                case ViewState::Empty: statusSymbol = '.'; break;
                case ViewState::Unknown: statusSymbol = '?'; break;
            }
            std::cout << std::setw(3) << statusSymbol;
        }
        std::cout << std::endl;
    }
}

void OutputProcessor::drawPlayerShips(ShipManager &shipManager) const {
    for (int i = 0; i < shipManager.getShipsCount(); i++) {
        std::cout << "Ship " << i + 1 << ": ";
        for (int j = 0; j < shipManager[i]->getLength(); j++) {
            if (j > 0) std::cout << "+";
            std::cout << shipManager[i]->getSegmentStatus(j);
        }
        std::cout << std::endl;
    }
}

void OutputProcessor::drawBoards(GameBoard &userBoard, GameBoard &aiBoard) const {
    OutputProcessor::showMessage("\033[34mYour board:\033[39m");
    drawBoard(userBoard);
    OutputProcessor::showMessage("");
    OutputProcessor::showMessage("\033[31mAI board:\033[39m");
    drawBoard(aiBoard);
}

void OutputProcessor::drawShips(ShipManager &userShipManager, ShipManager &aiShipManager) const {
    OutputProcessor::showMessage("\033[34mYour ships:\033[39m");
    drawPlayerShips(userShipManager);
    OutputProcessor::showMessage("");
    OutputProcessor::showMessage("\033[31mAI ships:\033[39m");
    drawPlayerShips(aiShipManager);
}
