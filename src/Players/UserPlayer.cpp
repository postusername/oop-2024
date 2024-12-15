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

    // TODO
    //oldOutputProcessor::showMessage("Placing \033[34myour ships:\033[39m");
    for (size_t i = 0; i < gameMode.shipLengths.size(); i++)
    {
        bool validInput = false;
        while (!validInput)
        {
            try
            {
                //TODO
                //oldOutputProcessor::showMessage("\033[1mSetting up Ship " + std::to_string(i + 1) +
                //                                "\033[0m (Length: " + std::to_string(gameMode.shipLengths[i]) + ")");

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

Option UserPlayer::makeMove(GameBoard &enemyBoard, ShipManager &enemyShipManager)
{
    bool validInput = false;
    Option chosenOption;
    while (!validInput)
    {
        try
        {
            chosenOption = inputProcessor.readOption();
            if (chosenOption == Option::UseAbilityAndShoot)
            {
                useSkill();
            }
            validInput = true;
        }
        catch (const NoAbilitiesAvailableException &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    if (chosenOption == Option::Shoot || chosenOption == Option::UseAbilityAndShoot)
    {
        attack(enemyBoard, enemyShipManager);
    }
    return chosenOption;
}

void UserPlayer::reset(const GameSettings &gameMode, GameBoard &enemyBoard, ShipManager &enemyShipManager)
{
    createShips(gameMode);
    skillManager = new SkillManager(inputProcessor, enemyBoard, enemyShipManager);
}

void UserPlayer::attack(GameBoard &enemyBoard, ShipManager &enemyShipManager)
{
    int aliveShipsCount = enemyShipManager.getAliveShipsCount();
    std::pair<size_t, size_t> coords;
    bool validInput = false;
    while (!validInput)
    {
        try
        {
            coords = InputProcessor::readCoords();
            size_t x = coords.first, y = coords.second;
            enemyBoard.attackCell(x, y, inputProcessor.getFlag(flagType::DoubleDamage) ? 2 : 1);
            validInput = true;
        }
        catch (const AttackCoordsException &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    if (enemyShipManager.getAliveShipsCount() < aliveShipsCount)
    {
        skillManager->addSkill();
    }
    inputProcessor.resetFlags();
}

void UserPlayer::useSkill()
{
    bool validInput = false;
    while (!validInput)
    {
        try
        {
            std::string ability_name = skillManager->applyAbility();
            validInput = true;
        }
        catch (const InvalidAbilityCoordsException &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
    if (inputProcessor.getFlag(flagType::Scanner))
    {
        if (inputProcessor.getFlag(flagType::ShipFound))
        {
            oldOutputProcessor::showMessage("Ship found!");
        }
        else
        {
            oldOutputProcessor::showMessage("Ship not found!");
        }
    }
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
