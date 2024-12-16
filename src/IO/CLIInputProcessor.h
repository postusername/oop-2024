#pragma once

#include <unordered_map>
#include <cstddef>
#include <limits>
#include "../Ship.h"
#include "../Game/GameSettings.h"

class InputProcessor {
private:
    std::unordered_map<flagType, bool> flags;
    Orientation readShipOrientation();
    static std::pair<size_t, size_t> readCoords(GameSettings& settings);

public:
    bool askForReset();
    Command askForCommand();
    std::pair<size_t, size_t> askForFirePoint(GameSettings& settings);
    std::pair<size_t, size_t> askForAbilityPoint(GameSettings& settings);
    GameSettings& getGameMode(GameSettings& settings);
    std::pair<std::vector <Orientation>, std::vector<std::pair<size_t, size_t>>> getInitialShips(GameSettings& settings);
};