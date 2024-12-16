#pragma once

#include "GameState.h"

template <typename RendererT>
class GameView {
    RendererT renderer;
public:
    GameView();
    void render(GameState* state);
    void print(std::string message);
};


template <typename RendererT>
GameView<RendererT>::GameView() : renderer(RendererT()) {

}

template <typename RendererT>
void GameView<RendererT>::render(GameState* state)
{
    renderer.show_message("\033[1mRound " + std::to_string(state->getRoundNumber()) + "\033[0m");
    renderer.draw_boards(state->getUser().getGameBoard(), state->getAI().getGameBoard());
    renderer.draw_ships(state->getUser().getShipManager(), state->getAI().getShipManager());
}

template <typename RendererT>
void GameView<RendererT>::print(std::string message) {
    renderer.show_message(message);
}
