#pragma once

#include <iostream>
#include "../GameBoard.h"
#include "../ShipManager.h"


template <typename BoardRendererT>
class CLIRenderer {
    BoardRendererT& renderer;
    std::string render_user_ships(ShipManager& shipManager);
public:
    CLIRenderer();
    void draw_boards(GameBoard& userBoard, GameBoard& aiBoard);
    void draw_ships(ShipManager& userShipManager, ShipManager& aiShipManager);
    void show_message(std::string message);
};
