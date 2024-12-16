#include "GameController.h"

template <typename InputProcessor, typename OutputProcessor>
GameController<InputProcessor, OutputProcessor>::GameController() : inputProcessor() {
    this->restart();
}

template <typename InputProcessor, typename OutputProcessor>
GameController<InputProcessor, OutputProcessor>::GameController(std::string filename) : inputProcessor() {
    try {
        this->game = new Game<OutputProcessor>(filename);
    } catch (std::exception e) {
        std::cerr << e.what() << std::endl;
    }
}

template <typename InputProcessor, typename OutputProcessor>
GameController<InputProcessor, OutputProcessor>::~GameController() {
    delete game;
}

template <typename InputProcessor, typename OutputProcessor>
void GameController<InputProcessor, OutputProcessor>::restart() {
    this->settings = this->inputProcessor->getGameMode();
    bool incorrect_input = true;
    
    while (incorrect_input) {
        try {
            auto [orientations, coords] = this->inputProcessor->getInitialShips(this->settings);
            this->game = Game(this->settings);
            incorrect_input = false;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}

template <typename InputProcessor, typename OutputProcessor>
void GameController<InputProcessor, OutputProcessor>::play() {
    while (true) {
        while (this->game->getRoundNumber() <= 3 &&
               this->game->getGameStatus() != GameStatus::GameOver &&
               this->game->getGameStatus() != GameStatus::Exit) {
            this->makeMove();
        }

        if (this->game->getGameStatus() != GameStatus::Exit) {
            bool restart = this->inputProcessor->askForReset();
            if (restart)
                this->restart();
            else
                break;
        }
    }
}


template <typename InputProcessor, typename OutputProcessor>
void GameController<InputProcessor, OutputProcessor>::makeMove() {
    Command user_choice = this->inputProcessor->askForCommand();
    if (user_choice == Command::Shoot) {
        auto [x, y] = this->inputProcessor->askForFirePoint(this->settings);
        this->game->shoot(x, y);
    } else if (user_choice == Command::UseAbility) {
        auto [x, y] = this->inputProcessor->askForFirePoint(this->settings);
        auto [ax, ay] = this->inputProcessor->askForAbilityPoint(this->settings);
        this->game->useAbilityAndShoot(x, y, ax, ay);
    } else if (user_choice == Command::Save) {
        std::string filename = this->inputProcessor->askForFilename();
        this->game->saveGame(filename);
    } else if (user_choice == Command::Load) {
        std::string filename = this->inputProcessor->askForFilename();
        try {
            Game<OutputProcessor>* saved_game = new Game<OutputProcessor>(filename);
            delete this->game;
            this->game = saved_game;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    } else if (user_choice == Command::Exit) {
        this->game->endGame();
    } else {
        std::cerr << "WTF man..." << std::endl;
    }

    if (this->game->getGameStatus() == GameStatus::GameWin)
        this->game->newRound(this->settings);
}
