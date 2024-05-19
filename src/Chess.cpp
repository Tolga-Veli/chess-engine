#include "../include/Chess.hpp"

void Chess::run() {
  SDL_Handler handler;

  Game *game = new Game();

  bool quit = false;
  std::string path = "";

  handler.renderChessboard();

  while (!quit) {
    while (SDL_PollEvent(&handler.event)) {
      switch (handler.event.type) {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
        path = handleMouseDown(handler, game);
        break;
      case SDL_MOUSEBUTTONUP:
        handleMouseUp(handler, game);
        break;
      }
    }
    SDL_Delay(1000);
  }

  delete game;
}

std::string Chess::handleMouseDown(SDL_Handler &handler, Game *&game) {

  int x = handler.event.button.x / handler.CELL_WIDTH;
  int y = handler.event.button.y / handler.CELL_WIDTH;

  handler.undoPieceRender(x, y);

    int clicked_Cell = (y * 😎 + x % 8;
    for (unsigned long long bitboard : game->bitboard_piece) {
    if (game->checkBitAtPos(bitboard, clicked_Cell)) {
    }
    }
}

void Chess::handleMouseUp(SDL_Handler &handler, Game *&game) {

  int x = handler.event.button.x / handler.CELL_WIDTH;
  int y = handler.event.button.y / handler.CELL_WIDTH;
}
