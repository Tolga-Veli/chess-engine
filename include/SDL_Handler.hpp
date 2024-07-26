#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

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
  static const int WINDOW_WIDTH = 800;
  static const int WINDOW_HEIGHT = 800;
  static const int CELL_WIDTH = WINDOW_WIDTH / 8;

  SDL_Event event;

public:
  SDL_Handler();
  ~SDL_Handler();

  void renderChessboard();
  void renderPiece(const std::string &name, int x, int y);
  void undoPiece(int x, int y);
};
