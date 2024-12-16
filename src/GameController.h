#pragma once

#include <string>
#include "Game/Game.h"
#include "IO/CLICommandHandler.h"


template <typename InputProcessor, typename OutputProcessor>
class GameController {
private:
    Game<OutputProcessor>* game;
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
