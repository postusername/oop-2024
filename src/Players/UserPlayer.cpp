#include "UserPlayer.h"

UserPlayer::UserPlayer(const GameSettings &gameMode, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords)
{
    this->createShips(gameMode, orientations, coords);
}

UserPlayer::UserPlayer(GameBoard &enemyBoard, ShipManager &enemyShipManager)
{
    this->userBoard = new GameBoard();
    this->userShipManager = new ShipManager();
    this->skillManager = new SkillManager(enemyBoard, enemyShipManager);
}

UserPlayer::~UserPlayer()
{
    delete userBoard;
    delete userShipManager;
    delete skillManager;
}

void UserPlayer::createShips(const GameSettings &gameMode,
                             std::vector<Orientation> orientations,
                             std::vector<std::pair<size_t, size_t>> coords)
{
    if (userBoard != nullptr || userShipManager != nullptr)
    {
        delete userBoard;
        delete userShipManager;
    }
    userBoard = new GameBoard(gameMode.boardSize, gameMode.boardSize);
    userShipManager = new ShipManager(gameMode.shipLengths);

    for (size_t i = 0; i < gameMode.shipLengths.size(); i++)
    {
        bool validInput = false;
        while (!validInput)
        {
            try
            {
                Orientation orientation = orientations[i];
                auto ccoords = coords[i];
                size_t x = ccoords.first, y = ccoords.second;

                Ship *currentShip = new Ship(gameMode.shipLengths[i], orientation, x, y);
                userShipManager->addShip(currentShip);

                userBoard->placeShip(x, y, currentShip);

                validInput = true;
            }
            catch (const ShipException &e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}

bool UserPlayer::isDefeated()
{
    return userShipManager->allShipsDestroyed();
}

GameBoard &UserPlayer::getGameBoard()
{
    return *userBoard;
}

ShipManager &UserPlayer::getShipManager()
{
    return *userShipManager;
}

SkillManager &UserPlayer::getAbilityManager()
{
    return *skillManager;
}

std::ostream &operator<<(std::ostream &os, const UserPlayer &player)
{
    os << *player.userBoard << '\n';
    os << *player.userShipManager << '\n';
    os << *player.skillManager << '\n';
    return os;
}

std::istream &operator>>(std::istream &is, UserPlayer &player)
{
    try
    {
        is >> *player.userBoard;
        is >> *player.userShipManager;
        for (auto i = 0; i < player.userShipManager->getShipsCount(); i++)
        {
            Ship *ship = player.userShipManager->operator[](i);
            player.userBoard->placeShip(ship->x, ship->y, ship);
        }
        is >> *player.skillManager;
    }
    catch (const std::ios_base::failure &e)
    {
        throw std::ios_base::failure("Error reading UserPlayer: " + std::string(e.what()));
    }
    return is;
}
