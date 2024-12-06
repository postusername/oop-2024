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

void GameState::saveGame() {
    try {
        std::ofstream outFile("game_state.txt");
        if (!outFile) {
            std::cerr << "Error opening file for saving game state!" << std::endl;
            return;
        }
        outFile << *this;
        outFile.close();
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    /*std::ifstream inFile("game_state.txt");
    if (!inFile) {
        std::cerr << "Error while reopening file for saving game state!" << std::endl;
        return;
    }

    unsigned short check_sum = 0;
    while (inFile.peek() != EOF ) {
        unsigned char byte;
        inFile >> byte;
        check_sum += byte;
    }
    inFile.close();

    std::ofstream realoutFile("game_state.txt", std::ios::trunc);
    if (!realoutFile) {
        std::cerr << "Error reopening file for saving game state!" << std::endl;
        return;
    }
    realoutFile << check_sum << '\n';
    realoutFile << *this;
    realoutFile.close();*/
    std::cout << "GameController state saved successfully!" << std::endl;
}

void GameState::loadGame(std::string filename) {
    try {
        std::ifstream inFile(filename);
        if (!inFile) {
            std::cerr << "Error opening file for loading game state!" << std::endl;
            return;
        }
        inFile >> *this;
        std::cout << "GameController state loaded successfully!" << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    /*unsigned short check_sum, file_sum;
    inFile >> file_sum;
    check_sum = 0;
    while (inFile.peek() != EOF) {
        unsigned char byte;
        inFile >> byte;
        check_sum += byte;
    }

    if (check_sum != file_sum) {
        std::cerr << "Saving is broken!" << std::endl;
        inFile.close();
        exit(1);
    }
    

    std::ifstream realinFile(filename);
    unsigned short cs; realinFile >> cs;*/
}

bool GameState::checkSave(std::ifstream* inFile) {
    return true;
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