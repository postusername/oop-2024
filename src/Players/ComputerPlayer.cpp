#include "ComputerPlayer.h"

void ComputerPlayer::makeMove(GameBoard& enemyBoard) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, enemyBoard.getWidth() - 1);
    size_t x = dis(gen);
    std::uniform_int_distribution<> dis2(0, enemyBoard.getHeight() - 1);
    size_t y = dis2(gen);
    enemyBoard.attackCell(x, y, 1);
}

bool ComputerPlayer::isDefeated() {
    return aiShipManager->allShipsDestroyed();
}

void ComputerPlayer::createShips(const GameSettings& gameMode) {
    if (aiBoard != nullptr || aiShipManager != nullptr) {
        delete aiBoard;
        delete aiShipManager;
    }

    aiBoard = new GameBoard(gameMode.boardSize, gameMode.boardSize);
    aiShipManager = new ShipManager(gameMode.shipLengths);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> orientationDist(0, 1);

    std::cout << "Generate \033[31mAI ships:\033[39m" << std::endl;
    for (unsigned short shipLength : gameMode.shipLengths) {
        std::vector<std::pair<unsigned short, unsigned short>> candidates;
        for (size_t x = 0; x < aiBoard->getWidth(); ++x) {
            for (size_t y = 0; y < aiBoard->getHeight(); ++y) {
                candidates.emplace_back(x, y);
            }
        }

        bool placed = false;
        std::shuffle(candidates.begin(), candidates.end(), gen);

        while (!placed && !candidates.empty()) {
            auto [startX, startY] = candidates.back();
            candidates.pop_back();
            bool isHorizontal = orientationDist(gen) == 1;

            Ship* currentShip = new Ship(shipLength, isHorizontal ? Orientation::Horizontal : Orientation::Vertical, startX, startY);
            try {
                std::cout << "\tLen: " << shipLength << ", start X=" << startX << ", start Y=" << startY << ", isHorizontal=" << isHorizontal << std::endl;
                aiBoard->placeShip(startX, startY, currentShip);
                aiShipManager->addShip(currentShip);
                placed = true;
            } catch (const ShipException&) {
                delete currentShip;
            }
        }

        if (!placed) {
            throw std::runtime_error("Failed to place all ships on the board!");
        }
    }
}

ComputerPlayer::ComputerPlayer() {
    this->aiBoard = new GameBoard();
    this->aiShipManager = new ShipManager();
}

ComputerPlayer::~ComputerPlayer() {
    delete aiBoard;
    delete aiShipManager;
}

GameBoard &ComputerPlayer::getGameBoard() {
    return *aiBoard;
}

ShipManager &ComputerPlayer::getShipManager() {
    return *aiShipManager;
}

std::ostream& operator<<(std::ostream& os, const ComputerPlayer& player) {
    os << *player.aiBoard << '\n';
    os << *player.aiShipManager << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, ComputerPlayer& player) {
    try {
        is >> *player.aiBoard;
        is >> *player.aiShipManager;
        for (auto i = 0; i < player.aiShipManager->getShipsCount(); i++) {
            Ship* ship = player.aiShipManager->operator[](i);
            player.aiBoard->placeShip(ship->x, ship->y, ship);
        }
    } catch (const std::ios_base::failure& e) {
        throw std::ios_base::failure("Error reading ComputerPlayer: " + std::string(e.what()));
    }
    return is;
}





