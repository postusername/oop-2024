#include "Game/Game.h"


int main(int argc, char** argv) {
    Game* game;
    if (argc > 2 && std::string(argv[1]) == "--save")
        game = new Game(argv[2]);
    else
        game = new Game();
    game->startNewGame();
    return 0;
}
