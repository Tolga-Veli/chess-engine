#include "../include/Chess.hpp"

void Chess::run() {
  SDL_Handler handler;
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
    handler.present_renderer();
    SDL_Delay(1000);
  }
}

void Chess::handleMouseDown(SDL_Handler &handler, std::unique_ptr<Game> &game) {
  int x = handler.event.button.x / CELL_WIDTH;
  int y = handler.event.button.y / CELL_WIDTH;

  if (game->piece_selected)
    game->move_piece(x % 8 + y * 8);
  else
    game->select_piece(x % 8 + y * 8);
}
