#include "GameController.h"
#include "IO/CLIInputProcessor.h"
#include "IO/CLICommandHandler.h"
#include "IO/CLIRenderer.h"
#include "IO/CLIBoardRenderer.h"


int main(int argc, char** argv) {
    GameController<CLIInputProcessor<CLICommandHandler>, CLIRenderer<CLIBoardRenderer>>* gc;
    if (argc > 2 && std::string(argv[1]) == "--save")
        gc = new GameController<CLIInputProcessor<CLICommandHandler>, CLIRenderer<CLIBoardRenderer>>(argv[2]);
    else
        gc = new GameController<CLIInputProcessor<CLICommandHandler>, CLIRenderer<CLIBoardRenderer>>();
    gc->play();
    return 0;
}
