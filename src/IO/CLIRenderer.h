#pragma once

#include <iostream>
#include "../GameBoard.h"
#include "../ShipManager.h"


template <typename BoardRendererT>
class CLIRenderer {
    BoardRendererT renderer;
    std::string render_user_ships(ShipManager& shipManager);
public:
    CLIRenderer();
    void draw_boards(GameBoard& userBoard, GameBoard& aiBoard);
    void draw_ships(ShipManager& userShipManager, ShipManager& aiShipManager);
    void show_message(std::string message);
};

template <typename BoardRendererT>
std::string CLIRenderer<BoardRendererT>::render_user_ships(ShipManager &shipManager)
{
    std::stringstream ss;
    for (int i = 0; i < shipManager.getShipsCount(); i++) {
        ss << "Ship " << i + 1 << ": ";
        for (int j = 0; j < shipManager[i]->getLength(); j++) {
            if (j > 0)
                ss << "+";
            ss << shipManager[i]->getSegmentStatus(j);
        }
        ss << std::endl;
    }
    return ss.str();
}

template <typename BoardRendererT>
CLIRenderer<BoardRendererT>::CLIRenderer() : renderer(BoardRendererT()) {}

template <typename BoardRendererT>
void CLIRenderer<BoardRendererT>::draw_boards(GameBoard& userBoard, GameBoard& aiBoard)
{
    std::cout << renderer.render(userBoard) << std::endl;
    std::cout << renderer.render(aiBoard) << std::endl;
}

template <typename BoardRendererT>
void CLIRenderer<BoardRendererT>::draw_ships(ShipManager &userShipManager, ShipManager &aiShipManager)
{
    this->show_message("\033[34mYour ships:\033[39m");
    std::cout << render_user_ships(userShipManager) << std::endl;
    this->show_message("\033[31mAI ships:\033[39m");
    std::cout << render_user_ships(aiShipManager) << std::endl;
}

template <typename BoardRendererT>
void CLIRenderer<BoardRendererT>::show_message(std::string message)
{
    std::cout << message << std::endl;
}