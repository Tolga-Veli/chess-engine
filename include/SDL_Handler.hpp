#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "fen.hpp"

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
  void renderChessboard();
  void renderPiece(int x, int y, std::string path);
  void undoPieceRender(int x, int y);
};
