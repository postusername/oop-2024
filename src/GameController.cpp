#include "GameController.h"

template<typename InputProcessor>
GameController<InputProcessor>::GameController():
    game(new game()), inputProcessor(new InputProcessor()) {}

template <typename InputProcessor>
GameController<InputProcessor>::~GameController() {
    delete game;
    delete inputProcessor;
}

template <typename InputProcessor>
void GameController<InputProcessor>::playGame() {
    game->newRound();
}

template <typename InputProcessor>
void GameController<InputProcessor>::makeMove() {

}
