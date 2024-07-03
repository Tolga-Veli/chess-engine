#include "../include/Chess.hpp"
#include <iostream>

void Chess::run() {
  SDL_Handler handler;
  handler.renderChessboard();
  std::unique_ptr<Game> game = std::make_unique<Game>();
  bool quit = false;

  while (!quit) {
    while (SDL_PollEvent(&handler.event)) {
      switch (handler.event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
        handleMouseDown(handler, game);
        break;
      default:
        break;
      }
    }
    SDL_Delay(1000);
  }
}

void Chess::handleMouseDown(SDL_Handler &handler, std::unique_ptr<Game> &game) {
  int x = handler.event.button.x / handler.CELL_WIDTH;
  int y = handler.event.button.y / handler.CELL_WIDTH;
}
