#pragma once

#include <unordered_map>
#include <cstddef>
#include <limits>
#include "../Ship.h"
#include "../Game/GameSettings.h"

enum class flagType {
    DoubleDamage,
    Scanner,
    ShipFound
};

enum class Option {
    Shoot = 1,
    UseAbilityAndShoot = 2,
    SaveGame = 3,
    Exit = 4,
    LoadGame = 5
};

class InputProcessor {
private:
    std::unordered_map<flagType, bool> flags;

public:
    static std::pair<size_t, size_t> readCoords();
    GameSettings* readGameMode();
    bool readStartNewGame();
    Orientation readShipOrientation();
    Option readOption();
    bool& getFlag(flagType flagName);
    void resetFlags();
};