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

class GameState {
private:
    size_t roundNumber;
    GameSettings gameMode;
    UserPlayer* user;
    ComputerPlayer* ai;

public:
    GameState(std::string filename);
    GameState(GameSettings gameMode, std::vector<Orientation> orientations, std::vector<std::pair<size_t, size_t>> coords);
    ~GameState();
    void incrementRoundNumber();
    size_t getRoundNumber() const;
    GameSettings getGameMode();
    UserPlayer& getUser();
    ComputerPlayer& getAI();

    void saveGame(std::string filename, bool calc_checksum = false);
    void loadGame(std::string filename, bool calc_checksum = true);
    friend std::ostream& operator<<(std::ostream& os, const GameState& state);
    friend std::istream& operator>>(std::istream& is, GameState& state);
};
