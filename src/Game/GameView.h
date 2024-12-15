#pragma once

#include "GameState.h"

template <typename RendererT>
class GameView {
    RendererT renderer;
public:
    GameView();
    GameView operator=(GameView&&) = default;
    void render(GameState* state);
    void print(std::string message);
};
