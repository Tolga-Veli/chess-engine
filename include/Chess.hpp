#pragma once

#include "Game.hpp"
#include "SDL_Handler.hpp"

namespace Chess {
void run();
void handleMouseDown(SDL_Handler &handler, Game *game);
} // namespace Chess
