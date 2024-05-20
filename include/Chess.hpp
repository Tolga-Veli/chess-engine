#pragma once

#include "Game.hpp"
#include "SDL_Handler.hpp"

namespace Chess {
static void run();
static void handleMouseDown(SDL_Handler &handler, Game *game);
} // namespace Chess
