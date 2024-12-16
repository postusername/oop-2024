#include "Game.h"


Game::Game(GameSettings settings, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords) {
    this->gameStatus = GameStatus::InProgress;
    this->view.print("Placing \033[34myour ships...\033[39m");
    this->gameState = new GameState(settings, orientations, coords);
    this->view = GameView<CLIRenderer<CLIBoardRenderer>>();
    
    this->view.print("Generate \033[31mAI ships...\033[39m");
    this->gameState->getAI().createShips(settings);

    this->view.render(this->gameState);
}

Game::Game(std::string filename) {
    this->gameStatus = GameStatus::InProgress;
    this->gameState = new GameState(filename);
    this->view = GameView<CLIRenderer<CLIBoardRenderer>>();
    this->view.print("Game state loaded successfully!");

    this->view.render(this->gameState);
}

void Game::shoot(size_t x, size_t y, bool double_damage = false) {
    int aliveShipsCount = this->gameState->getAI().getShipManager().getAliveShipsCount();
    this->gameState->getAI().getGameBoard().attackCell(x, y, double_damage ? 2 : 1);
    if (this->gameState->getAI().getShipManager().getAliveShipsCount() < aliveShipsCount) {
        this->gameState->getUser().getAbilityManager().addSkill();
    }

    this->ai_move();
    this->view.render(this->gameState);
}

void Game::useAbilityAndShoot(size_t x, size_t y, size_t ax, size_t ay)
{
    std::string ability_name = this->gameState->getUser().getAbilityManager().applyAbility(ax, ay);
    this->view.print(ability_name + " ability applied!");
    bool double_damage = false;
    if (ability_name == "DoubleDamage")
        double_damage = true;
    else if (ability_name == "Scanner") {
        if (this->gameState->getAI().getGameBoard().ship_found)
            this->view.print("Ship found!");
        else
            this->view.print("Ship does not found!");
    }
    this->shoot(x, y, double_damage);
}

void Game::saveGame(std::string filename) {
    try {
        this->gameState->saveGame(filename);
        this->view.print("Game state saved successfully!");
    } catch (std::exception e) {
        this->view.print(e.what());
    }
}

void Game::newRound(GameSettings &settings) {
    gameState->incrementRoundNumber();

    this->gameStatus = GameStatus::InProgress;
    this->view.print("New round!");
    this->view.print("Generate \033[31mAI ships...\033[39m");
    this->gameState->getAI().createShips(settings);

    this->view.render(this->gameState);
}

void Game::endGame() {
    this->gameStatus = GameStatus::Exit;
}

void Game::ai_move()
{
    this->gameState->getAI().makeMove(this->gameState->getUser().getGameBoard());
    if (gameState->getUser().isDefeated()) {
        gameStatus = GameStatus::GameOver;
        this->view.print("Your ships are destroyed! Game Over!");
    } else if (gameState->getAI().isDefeated()) {
        gameStatus = GameStatus::GameWin;
        this->view.print("AI Defeated! Next Round!");
    }
}

GameStatus Game::getGameStatus() {
    return this->gameStatus;
}

size_t Game::getRoundNumber()
{
    return this->gameState->getRoundNumber();
}

Game::~Game() {
    delete gameState;
}

