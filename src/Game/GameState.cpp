#include "GameState.h"

GameState::GameState(std::string filename)
{
    this->gameMode = GameSettings();
    this->loadGame(filename);
}

GameState::GameState(GameSettings gameMode, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords) 
{
    this->roundNumber = 1;
    this->gameMode = gameMode;
    this->ai = new ComputerPlayer();
    this->ai->createShips(gameMode);
    this->user = new UserPlayer(this->ai->getGameBoard(), this->ai->getShipManager());
    this->user->createShips(gameMode, orientations, coords);
}

GameState::~GameState()
{
    delete user;
    delete ai;
}

void GameState::incrementRoundNumber()
{
    roundNumber++;
}

size_t GameState::getRoundNumber() const
{
    return roundNumber;
}

UserPlayer &GameState::getUser()
{
    return *user;
}

ComputerPlayer &GameState::getAI()
{
    return *ai;
}

GameSettings GameState::getGameMode()
{
    return gameMode;
}

void GameState::saveGame(std::string filename, bool calc_checksum)
{
    std::ifstream inFile;
    unsigned char check_sum = 0;

    if (calc_checksum)
    {
        inFile.open(filename); // НЕ РАБОТАЕТ ЕСЛИ ОТКРЫТЬ В КОНСТРУКТОРЕ ИЛИ СОЗДАТЬ ТУТ
        if (!inFile) {
            throw std::invalid_argument("Error while reopening file for saving game state!");
        }

        while (inFile.peek() != EOF)
        {
            unsigned char byte;
            inFile >> byte;
            check_sum ^= byte;
        }
        inFile.close();
    }

    std::ofstream outFile(filename, std::ios::trunc | std::ios::binary);
    if (!outFile) {
        throw std::invalid_argument("Error while opening file for saving game state!");
    }
    if (calc_checksum)
        outFile << check_sum << '\n';
    outFile << *this;
    outFile.close();
    if (!calc_checksum)
        saveGame(filename, !calc_checksum);
}

void GameState::loadGame(std::string filename, bool calc_checksum)
{
    unsigned char check_sum = 0;
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile) {
        throw std::invalid_argument("Error while opening file for loading game state!");
    }

    if (calc_checksum)
    {
        while (inFile.peek() != EOF)
        {
            unsigned char byte;
            inFile >> byte;
            check_sum ^= byte;
        }
        inFile.close();

        if (check_sum != 0) {
            throw std::invalid_argument("Saving is broken!");
        }

        loadGame(filename, !calc_checksum);
    }
    else
    {
        inFile >> check_sum;
        inFile >> *this;
    }
}

std::ostream &operator<<(std::ostream &os, const GameState &state)
{
    os << state.roundNumber << '\n';
    os << state.gameMode << '\n';
    os << *state.ai << '\n';
    os << *state.user << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, GameState &state)
{
    try
    {
        is >> state.roundNumber;
        is >> state.gameMode;
        state.ai = new ComputerPlayer();
        is >> *state.ai;
        state.user = new UserPlayer(state.ai->getGameBoard(), state.ai->getShipManager());
        is >> *state.user;
    }
    catch (const std::ios_base::failure &e)
    {
        throw std::ios_base::failure("Error reading GameState: " + std::string(e.what()));
    }
    return is;
}