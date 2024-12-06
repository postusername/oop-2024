#pragma once

#include "../Players/ComputerPlayer.h"
#include "../Players/UserPlayer.h"
#include "../IO/InputProcessor.h"
#include "../IO/OutputProcessor.h"
#include "GameSettings.h"
#include "GameState.h"

enum class GameStatus {
    InProgress,
    GameOver,
    Exit
};

class GameController {
private:
    OutputProcessor* outputProcessor;
    InputProcessor* inputProcessor;
    bool userTurn;
    GameStatus gameStatus;
    GameState* gameState;
    bool from_save;
public:
    GameController();
    GameController(std::string filename);
    ~GameController();
    void startNewGame();
    void playRound(bool from_save);
    void makeMove();
};