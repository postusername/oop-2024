#include "GameState.h"

GameState::GameState(std::string filename, InputProcessor* inputProcessor) :
    inputProcessor(inputProcessor)
{
    this->gameMode = new GameSettings();
    this->loadGame(filename);
}

GameState::GameState(GameSettings* gameMode, InputProcessor* inputProcessor)
    : roundNumber(1),
    gameMode(gameMode),
    inputProcessor(inputProcessor),
    user(new UserPlayer(*inputProcessor)),
    ai(new ComputerPlayer()) {}

GameState::~GameState() {
    delete user;
    delete ai;
}

void GameState::incrementRoundNumber() {
    roundNumber++;
}

void GameState::resetRoundNumber() {
    roundNumber = 1;
}

size_t GameState::getRoundNumber() const {
    return roundNumber;
}

UserPlayer &GameState::getUser() {
    return *user;
}

ComputerPlayer &GameState::getAI() {
    return *ai;
}

GameSettings &GameState::getGameMode() {
    return *gameMode;
}

void GameState::saveGame(std::string filename, bool calc_checksum) {
    std::ifstream inFile;
    unsigned char check_sum = 0;

    if (calc_checksum) {
        inFile.open(filename); // НЕ РАБОТАЕТ ЕСЛИ ОТКРЫТЬ В КОНСТРУКТОРЕ ИЛИ СОЗДАТЬ ТУТ
        if (!inFile) {
            std::cerr << "Error while reopening file for saving game state!" << std::endl;
            exit(1);
        }

        while (inFile.peek() != EOF) {
            unsigned char byte;
            inFile >> byte;
            check_sum ^= byte;
        }
        inFile.close();
    }

    std::ofstream outFile(filename, std::ios::trunc | std::ios::binary);
    if (!outFile) {
        std::cerr << "Error opening file for saving game state!" << std::endl;
        exit(1);
    }
    if (calc_checksum)
        outFile << check_sum << '\n';
    outFile << *this;
    outFile.close();
    if (calc_checksum)
        std::cout << "GameController state saved successfully!" << std::endl;
    else
        saveGame(filename, !calc_checksum);
}

void GameState::loadGame(std::string filename, bool calc_checksum) {
    unsigned char check_sum = 0;
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error opening file for loading game state!" << std::endl;
        exit(1);
    }
    
    if (calc_checksum) {
        while (inFile.peek() != EOF) {
            unsigned char byte;
            inFile >> byte;
            check_sum ^= byte;
        }
        inFile.close();

        if (check_sum != 0) {
            std::cerr << "Saving is broken!" << std::endl;
            exit(1);
        }

        loadGame(filename, !calc_checksum);
    } else {
        inFile >> check_sum;
        inFile >> *this;
        std::cout << "GameController state loaded successfully!" << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const GameState& state) {
    os << state.roundNumber << '\n';
    os << *state.gameMode << '\n';
    os << *state.ai << '\n';
    os << *state.user << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, GameState& state) {
    try {
        is >> state.roundNumber;
        is >> *state.gameMode;
        state.ai = new ComputerPlayer();
        is >> *state.ai;
        state.user = new UserPlayer(*(state.inputProcessor), state.ai->getGameBoard(), state.ai->getShipManager());
        is >> *state.user;
    } catch (const std::ios_base::failure& e) {
        throw std::ios_base::failure("Error reading GameState: " + std::string(e.what()));
    }
    return is;
}