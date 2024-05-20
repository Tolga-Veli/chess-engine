#include "../include/Chess.hpp"

void Chess::run() {
  SDL_Handler handler;

  Game *game = new Game();

  bool quit = false;

  handler.renderChessboard(game);

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

  delete game;
}

void Chess::handleMouseDown(SDL_Handler &handler, Game *game) {
  int x = handler.event.button.x / handler.CELL_WIDTH;
  int y = handler.event.button.y / handler.CELL_WIDTH;

  if (game->selectPiece(x, y)) {
    if (!game->pieceSelected) {
      handler.selectPieceGraphics(x, y);
      game->pieceSelected = true;
    } else {
      handler.renderPiece(x, y, game);
    }
  }
}
