#pragma once
#include "Game.hpp"
#include "SDL_Handler.hpp"
#include <memory>

namespace Chess {
void run();
void handleMouseDown(SDL_Handler &handler, std::unique_ptr<Game> &game);
} // namespace Chess
