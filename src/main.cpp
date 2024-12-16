#include "GameController.h"
#include "IO/CLICommandHandler.h"
#include "IO/CLIBoardRenderer.h"
#include "IO/CLIInputProcessor.h"
#include "IO/CLIRenderer.h"

typedef GameController<CLIInputProcessor<CLICommandHandler>, CLIRenderer<CLIBoardRenderer>> CLIGameController;


int main(int argc, char** argv) {
    CLIGameController* gc;
    if (argc > 2 && std::string(argv[1]) == "--save")
        gc = new CLIGameController(argv[2]);
    else
        gc = new CLIGameController();
    gc->play();
    return 0;
}
