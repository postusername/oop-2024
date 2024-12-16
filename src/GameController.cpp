#include "GameController.h"

template<typename InputProcessor>
GameController<InputProcessor>::GameController(Game &game, InputProcessor &InputProcessor):
    game(game), inputProcessor(InputProcessor) {}
