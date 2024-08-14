#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define CELL_WIDTH 100

class SDL_Handler {
private:
  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;

  std::map<std::string, SDL_Texture *> textures;

private:
  bool init();
  void SDL_cleanup();
  SDL_Texture *loadTextureFromFile(const std::string &path);

public:
  SDL_Event event;

public:
  SDL_Handler();
  ~SDL_Handler();

  void presentRenderer();
  void highlightSquare(int x, int y);
  void renderChessboard();
  void renderPiece(const std::string &name, int x, int y);
  void undoPiece(int x, int y);
};
