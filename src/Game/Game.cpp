#include "Game.h"

Game::Game(GameSettings settings, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords) {
    this->gameStatus = GameStatus::InProgress;
    this->gameState = new GameState(settings, orientations, coords);
    this->view = GameView<CLIRenderer<CLIBoardRenderer>>();
}

Game::Game(std::string filename) {
    this->gameStatus = GameStatus::InProgress;
    this->gameState = new GameState(filename);
    this->view = GameView<CLIRenderer<CLIBoardRenderer>>();
}

void Game::shoot(size_t x, size_t y, bool double_damage = false) {
    int aliveShipsCount = this->gameState->getAI().getShipManager().getAliveShipsCount();
    this->gameState->getAI().getGameBoard().attackCell(x, y, double_damage ? 2 : 1);
    if (this->gameState->getAI().getShipManager().getAliveShipsCount() < aliveShipsCount) {
        this->gameState->getUser().getAbilityManager().addSkill();
    }
    this->view.render(this->gameState);
}

void Game::useAbilityAndShoot(size_t x, size_t y)
{
    std::string ability_name = this->gameState->getUser().getAbilityManager().applyAbility();
    bool double_damage = false;
    //TODO
    //if (...)
    this->shoot(x, y, double_damage);
}

void Game::saveGame(std::string filename) {
    this->gameState->saveGame(filename);
    this->view.print("Game succefully saved!");
}

Game::~Game() {
    delete gameState;
}

