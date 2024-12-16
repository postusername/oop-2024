#pragma once


#include "../Players/ComputerPlayer.h"
#include "../Players/UserPlayer.h"
#include "GameView.h"
#include "GameState.h"


enum class GameStatus {
    InProgress,
    GameOver,
    GameWin,
    Exit
};

template <typename RendererT>
class Game {
private:
    GameStatus gameStatus;
    GameState* gameState;
    GameView<RendererT> view;

    void ai_move();
public:
    Game(GameSettings settings, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords);
    Game(std::string filename);

    void shoot(size_t x, size_t y, bool double_damage = false);
    void useAbilityAndShoot(size_t x, size_t y, size_t ax, size_t ay);
    void saveGame(std::string filename);

    void newRound(GameSettings& settings);
    void endGame();

    GameStatus getGameStatus();
    GameState* getGameState();
    size_t getRoundNumber();

    ~Game();
};


template <typename RendererT>
Game<RendererT>::Game(GameSettings settings, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords) : view(GameView<RendererT>()){
    this->gameStatus = GameStatus::InProgress;
    this->view.print("Placing \033[34myour ships...\033[39m");
    this->gameState = new GameState(settings, orientations, coords);
    
    this->view.print("Generate \033[31mAI ships...\033[39m");
    this->gameState->getAI().createShips(settings);

    this->view.render(this->gameState);
}

template <typename RendererT>
Game<RendererT>::Game(std::string filename) : view(GameView<RendererT>()) {
    this->gameStatus = GameStatus::InProgress;
    this->gameState = new GameState(filename);
    this->view.print("Game state loaded successfully!");

    this->view.render(this->gameState);
}

template <typename RendererT>
void Game<RendererT>::shoot(size_t x, size_t y, bool double_damage) {
    int aliveShipsCount = this->gameState->getAI().getShipManager().getAliveShipsCount();
    this->gameState->getAI().getGameBoard().attackCell(x, y, double_damage ? 2 : 1);
    if (this->gameState->getAI().getShipManager().getAliveShipsCount() < aliveShipsCount) {
        this->gameState->getUser().getAbilityManager().addSkill(this->gameState->getAI().getGameBoard(),
                                                                this->gameState->getAI().getShipManager());
    }

    this->ai_move();
    this->view.render(this->gameState);
}

template <typename RendererT>
void Game<RendererT>::useAbilityAndShoot(size_t x, size_t y, size_t ax, size_t ay)
{
    try {
        std::string ability_name = this->gameState->getUser().getAbilityManager().applyAbility(ax, ay, this->gameState->getAI().getGameBoard(), this->gameState->getAI().getShipManager());
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
    } catch (NoAbilitiesAvailableException e) {
        this->view.print("No abilities available!");
    }
}

template <typename RendererT>
void Game<RendererT>::saveGame(std::string filename) {
    try {
        this->gameState->saveGame(filename);
        this->view.print("Game state saved successfully!");
    } catch (std::exception e) {
        this->view.print(e.what());
    }
}

template <typename RendererT>
void Game<RendererT>::newRound(GameSettings &settings) {
    gameState->incrementRoundNumber();

    this->gameStatus = GameStatus::InProgress;
    this->view.print("New round!");
    this->view.print("Generate \033[31mAI ships...\033[39m");
    this->gameState->getAI().createShips(settings);

    this->view.render(this->gameState);
}

template <typename RendererT>
void Game<RendererT>::endGame() {
    this->gameStatus = GameStatus::Exit;
}

template <typename RendererT>
void Game<RendererT>::ai_move()
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

template <typename RendererT>
GameStatus Game<RendererT>::getGameStatus() {
    return this->gameStatus;
}

template <typename RendererT>
size_t Game<RendererT>::getRoundNumber()
{
    return this->gameState->getRoundNumber();
}

template <typename RendererT>
inline GameState *Game<RendererT>::getGameState()
{
    return this->gameState;
}

template <typename RendererT>
Game<RendererT>::~Game() {
    delete gameState;
}

