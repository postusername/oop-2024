#include "Game/GameController.h"


int main(int argc, char** argv) {
    GameController* game;
    if (argc > 2 && std::string(argv[1]) == "--save")
        game = new GameController(argv[2]);
    else
        game = new GameController();
    game->startNewGame();
    return 0;
}
