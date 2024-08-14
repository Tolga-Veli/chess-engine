#include "../include/Chess.hpp"

void Chess::run() {
  SDL_Handler handler;
  std::unique_ptr<Game> game = std::make_unique<Game>(handler);

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
    handler.presentRenderer();
    SDL_Delay(500);
  }
}

void Chess::handleMouseDown(SDL_Handler &handler, std::unique_ptr<Game> &game) {
  int x = handler.event.button.x / CELL_WIDTH;
  int y = handler.event.button.y / CELL_WIDTH;

  if (game->pieceSelected)
    game->movePiece(x % 8 + y * 8);
  else
    game->selectPiece(x % 8 + y * 8);
}
