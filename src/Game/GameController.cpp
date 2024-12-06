#include "GameController.h"

GameController::GameController()
    : outputProcessor(new OutputProcessor()),
      inputProcessor(new InputProcessor()),
      userTurn(true),
      gameStatus(GameStatus::InProgress),
      gameState(new GameState(inputProcessor->readGameMode(), inputProcessor)),
      from_save(false) {}

GameController::GameController(std::string filename) : outputProcessor(new OutputProcessor()),
    inputProcessor(new InputProcessor()),
    userTurn(true),
    gameStatus(GameStatus::InProgress),
    from_save(true)
{
    this->gameState = new GameState(filename, inputProcessor);
}

GameController::~GameController() {
    delete gameState;
    delete inputProcessor;
    delete outputProcessor;
}

void GameController::startNewGame() {
    while (gameStatus != GameStatus::Exit) {
        if (!from_save) {
            GameSettings& gameMode = gameState->getGameMode();
            gameState->getAI().createShips(gameMode);
            GameBoard& aiBoard = gameState->getAI().getGameBoard();
            ShipManager& aiShipManager = gameState->getAI().getShipManager();
            gameState->getUser().reset(gameMode, aiBoard, aiShipManager);
            gameState->resetRoundNumber();
        }

        while (gameState->getRoundNumber() <= 3 && gameStatus == GameStatus::InProgress) {
            playRound(from_save);
        }

        if (gameState->getRoundNumber() > 3) {
            OutputProcessor::showMessage("You Won!");
        } else {
            OutputProcessor::showMessage("You Lost!");
        }

        gameStatus = inputProcessor->readStartNewGame() ? GameStatus::InProgress : GameStatus::Exit;
    }
}

void GameController::playRound(bool from_save) {
    OutputProcessor::showMessage("\033[1mRound " + std::to_string(gameState->getRoundNumber()) + "\033[0m");
    if (gameState->getRoundNumber() > 1 || !from_save){
        gameState->getAI().createShips(gameState->getGameMode());
    }

    while (gameStatus == GameStatus::InProgress) {
        if (gameState->getUser().isDefeated()) {
            gameStatus = GameStatus::GameOver;
            OutputProcessor::showMessage("Your ships are destroyed! GameController Over!");
            break;
        } else if (gameState->getAI().isDefeated()) {
            OutputProcessor::showMessage("AI Defeated! Next Round!");
            gameState->incrementRoundNumber();
            break;
        }
        makeMove();
    }

}

void GameController::makeMove() {
    std::cout << std::endl;
    std::cout << "\033[1mДоступные способности:\033[0m" << std::endl;
    gameState->getUser().getAbilityManager().showAbilities();

    if (userTurn) {
        outputProcessor->drawBoards(gameState->getUser().getGameBoard(), gameState->getAI().getGameBoard());
        outputProcessor->drawShips(gameState->getUser().getShipManager(), gameState->getAI().getShipManager());

        GameBoard& aiBoard = gameState->getAI().getGameBoard();
        ShipManager& aiShipManager = gameState->getAI().getShipManager();
        Option userChoice = gameState->getUser().makeMove(aiBoard, aiShipManager);
        switch (userChoice) {
            case Option::Exit:
                gameStatus = GameStatus::Exit;
                return;
            case Option::SaveGame:
                gameState->saveGame("game_state.txt");
                return;
            case Option::LoadGame:
                gameState->loadGame("game_state.txt");
                return;
        }
    } else {
        gameState->getAI().makeMove(gameState->getUser().getGameBoard());
    }
    userTurn = !userTurn;
}
