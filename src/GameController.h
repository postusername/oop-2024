#pragma once

#include "Game/Game.h"

template <typename InputProcessor>
class GameController {
private:
    Game& game;
    InputProcessor& inputProcessor;

public:
    GameController();
    ~GameController();
    void playRound();
    void makeMove();
};
