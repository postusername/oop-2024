#pragma once


#include "../Players/ComputerPlayer.h"
#include "../Players/UserPlayer.h"
#include "../IO/CLIBoardRenderer.h"
#include "../IO/CLIRenderer.h"
#include "GameView.h"
#include "GameState.h"


enum class GameStatus {
    InProgress,
    GameOver,
    GameWin,
    Exit
};

class Game {
private:
    GameStatus gameStatus;
    GameState* gameState;

    GameView<CLIRenderer<CLIBoardRenderer>> view;

    void ai_move();
public:
    Game(GameSettings settings, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords);
    Game(std::string filename);

    void shoot(size_t x, size_t y, bool double_damage);
    void useAbilityAndShoot(size_t x, size_t y, size_t ax, size_t ay);
    void saveGame(std::string filename);

    void newRound(GameSettings& settings);
    void endGame();

    GameStatus getGameStatus();
    size_t getRoundNumber();

    ~Game();
};
