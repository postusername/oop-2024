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
