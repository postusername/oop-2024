#include <sstream>
#include "CLIBoardRenderer.h"


std::string CLIBoardRenderer::render(GameBoard &board) {
    std::stringstream ss;
    ss << "   ";
    auto height = board.getHeight();
    auto width = board.getWidth();
    for (size_t j = 0; j < width; ++j) {
        ss << std::setw(3) << j + 1;
    }
    ss << std::endl;
    ss << "   ";
    for (size_t j = 0; j < width; ++j) {
        ss << "---";
    }
    ss << std::endl;

    for (size_t i = 0; i < height; ++i) {
        ss << std::setw(2) << i + 1 << "|";
        for (size_t j = 0; j < width; ++j) {
            char statusSymbol;
            switch (board(j, i).getStatus()) {
                case ViewState::Ship: statusSymbol = '#'; break;
                case ViewState::Destroyed: statusSymbol = 'X'; break;
                case ViewState::Empty: statusSymbol = '.'; break;
                case ViewState::Unknown: statusSymbol = '?'; break;
            }
            ss << std::setw(3) << statusSymbol;
        }
        ss << std::endl;
    }

    return ss.str();
}
