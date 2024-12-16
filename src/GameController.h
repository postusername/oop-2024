#pragma once

#include "Game/Game.h"

enum class Command {
    Shoot,
    UseAbility,
    Save,
    Load,
    Exit
};

template <typename InputProcessor>
class GameController {
private:
    Game& game;
    InputProcessor& inputProcessor;
public:
    GameController(Game& game, InputProcessor& InputProcessor);
};

template<typename InputProcessor>
GameController<InputProcessor>::GameController(Game &game, InputProcessor &inputProcessor):
    game(game), inputProcessor(inputProcessor) {}
