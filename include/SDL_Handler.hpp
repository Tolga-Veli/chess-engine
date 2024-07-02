#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "fen.hpp"

class SDL_Handler : public FEN {
private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;

private:
  bool init();
  void SDL_cleanup();
  SDL_Texture *loadTextureFromFile(std::string path);

  void renderPiece(int x, int y);
  void undoPiece(int x, int y);

public:
  const int WINDOW_WIDTH = 800;
  const int WINDOW_HEIGHT = 800;
  const int CELL_WIDTH = WINDOW_WIDTH / 8;

  SDL_Event event;

public:
  SDL_Handler();
  ~SDL_Handler();

  void renderChessboard();
};
