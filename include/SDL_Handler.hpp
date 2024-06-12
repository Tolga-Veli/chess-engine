#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Game.hpp"

class SDL_Handler : FEN {
public:
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 800;
  const int CELL_WIDTH = WINDOW_WIDTH / 8;

  SDL_Window *window;
  SDL_Surface *surfaceScreen;
  SDL_Renderer *renderer;
  SDL_Event event;

  SDL_Handler();
  ~SDL_Handler();
  bool init();
  void SDL_cleanup();
  SDL_Texture *loadImageFromFile(std::string path);

  void renderChessboard(Game *game);
  void renderPiece(int x, int y, Game *game);
  void undoPiece(int x, int y, Game *game);

  void selectPiece(int x, int y, Game *game);
  void movePiece(int x, int y, Game *game);
};
