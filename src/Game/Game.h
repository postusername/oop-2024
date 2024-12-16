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
    GameWin
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
    void useAbilityAndShoot(size_t x, size_t y);
    void saveGame(std::string filename);

    void new_round(GameSettings& settings);

    GameStatus getGameStatus();

    ~Game();
};
