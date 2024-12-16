#pragma once

#include <unordered_map>
#include <cstddef>
#include <limits>
#include "../Ship.h"
#include "../Game/GameSettings.h"
#include "CLICommandHandler.h"


template <typename CommandHandlerT>
class CLIInputProcessor {
private:
    CommandHandlerT command_handler;

    Orientation readShipOrientation();
    std::pair<size_t, size_t> readCoords(GameSettings& settings);
public:
    CLIInputProcessor();
    bool askForReset();
    Command askForCommand();
    std::pair<size_t, size_t> askForFirePoint(GameSettings& settings);
    std::pair<size_t, size_t> askForAbilityPoint(GameSettings& settings);
    GameSettings getGameMode();
    std::pair<std::vector <Orientation>, std::vector<std::pair<size_t, size_t>>> getInitialShips(GameSettings& settings);
};