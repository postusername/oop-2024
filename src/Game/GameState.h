#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

#include "GameSettings.h"
#include "../GameBoard.h"
#include "../ShipManager.h"
#include "../SkillManager.h"
#include "../Players/ComputerPlayer.h"
#include "../Players/UserPlayer.h"
#include "../IO/InputProcessor.h"

class GameState {
private:
    size_t roundNumber;
    GameSettings* gameMode;
    InputProcessor* inputProcessor;
    UserPlayer* user;
    ComputerPlayer* ai;

public:
    GameState(std::string filename, InputProcessor* inputProcessor);
    GameState(GameSettings* gameMode, InputProcessor* inputProcessor);
    ~GameState();
    void incrementRoundNumber();
    void resetRoundNumber();
    size_t getRoundNumber() const;
    GameSettings& getGameMode();
    UserPlayer& getUser();
    ComputerPlayer& getAI();

    void saveGame(std::string filename, bool calc_checksum = false);
    void loadGame(std::string filename, bool calc_checksum = true);
    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
    friend std::istream& operator>>(std::istream& is, GameState& state);
};
