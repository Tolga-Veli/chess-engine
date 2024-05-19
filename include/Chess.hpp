#pragma once

#include "Game.hpp"
#include "SDL_Handler.hpp"

namespace Chess {
static void run();

static std::string handleMouseDown(SDL_Handler &handler, Game *&game);
static void handleMouseUp(SDL_Handler &handler, Game *&game);
} // namespace Chess
