#include "oldGame.h"

oldGame::oldGame()
    : oldOutputProcessor(new oldOutputProcessor()),
      inputProcessor(new InputProcessor()),
      userTurn(true),
      gameStatus(GameStatus::InProgress),
      gameState(new GameState(inputProcessor->readGameMode(), inputProcessor)),
      from_save(false) {}

oldGame::oldGame(std::string filename) : oldOutputProcessor(new oldOutputProcessor()),
    inputProcessor(new InputProcessor()),
    userTurn(true),
    gameStatus(GameStatus::InProgress),
    from_save(true)
{
    this->gameState = new GameState(filename, inputProcessor);
}

oldGame::~oldGame() {
    delete gameState;
    delete inputProcessor;
    delete oldOutputProcessor;
}

void oldGame::startNewGame() {
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
            oldOutputProcessor::showMessage("You Won!");
        } else {
            oldOutputProcessor::showMessage("You Lost!");
        }

        gameStatus = inputProcessor->readStartNewGame() ? GameStatus::InProgress : GameStatus::Exit;
    }
}

void oldGame::playRound(bool from_save) {
    oldOutputProcessor::showMessage("\033[1mRound " + std::to_string(gameState->getRoundNumber()) + "\033[0m");
    if (gameState->getRoundNumber() > 1 || !from_save){
        gameState->getAI().createShips(gameState->getGameMode());
    }

    while (gameStatus == GameStatus::InProgress) {
        if (gameState->getUser().isDefeated()) {
            gameStatus = GameStatus::GameOver;
            oldOutputProcessor::showMessage("Your ships are destroyed! Game Over!");
            break;
        } else if (gameState->getAI().isDefeated()) {
            oldOutputProcessor::showMessage("AI Defeated! Next Round!");
            gameState->incrementRoundNumber();
            break;
        }
        makeMove();
    }

}

void oldGame::makeMove() {
    if (userTurn) {
        oldOutputProcessor->drawBoards(gameState->getUser().getGameBoard(), gameState->getAI().getGameBoard());
        oldOutputProcessor->drawShips(gameState->getUser().getShipManager(), gameState->getAI().getShipManager());

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
