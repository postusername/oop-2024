#pragma once

#include "../Players/ComputerPlayer.h"
#include "../Players/UserPlayer.h"
#include "../IO/CLIBoardRenderer.h"
#include "../IO/CLIRenderer.h"
#include "GameView.h"
#include "GameSettings.h"
#include "GameState.h"

enum class GameStatus {
    InProgress,
    GameOver,
    Exit
};

class oldGame {
private:
    GameView<CLIRenderer<CLIBoardRenderer>> view;
    bool userTurn;
    GameStatus gameStatus;
    GameState* gameState;
    bool from_save;
public:
    oldGame();
    oldGame(std::string filename);
    ~oldGame();
    void startNewGame();
    void playRound(bool from_save);
    void makeMove();
};