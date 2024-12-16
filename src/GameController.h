#pragma once

#include <string>
#include "Game/Game.h"
#include "../IO/CLICommandHandler.h"

template <typename InputProcessor>
class GameController {
private:
    Game* game;
    InputProcessor inputProcessor;
    GameSettings settings;
public:
    GameController();
    GameController(std::string filename);
    ~GameController();
    void restart();
    void play();
    void makeMove();
};
