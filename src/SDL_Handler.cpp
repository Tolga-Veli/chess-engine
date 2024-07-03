#include "../include/SDL_Handler.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

bool SDL_Handler::init() {
  mWindow =
      SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE);

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Unable to initialise SDL: " << SDL_GetError() << '\n';
    return false;
  } else if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))) {
    std::cout << "Unable to initialise SDL_image: " << IMG_GetError() << '\n';
    return false;
  } else if (mWindow == nullptr) {
    std::cout << "Unable to create window: " << SDL_GetError() << '\n';
    return false;
  } else if (mRenderer == nullptr) {
    std::cout << "Unable to create renderer: " << SDL_GetError() << '\n';
    return false;
  }

  return true;
}

void SDL_Handler::SDL_cleanup() {
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);

  IMG_Quit();
  SDL_Quit();
}

SDL_Texture *SDL_Handler::loadTextureFromFile(std::string path) {
  return SDL_CreateTextureFromSurface(mRenderer, IMG_Load(path.c_str()));
}

void SDL_Handler::renderChessboard() {
  // Set the destination rectangle to cover the entire window
  SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

  SDL_Texture *backgroundTexture = loadTextureFromFile("chessboard.png");
  if (backgroundTexture == nullptr) {
    std::cout << "textureScreen was a nullptr" << SDL_GetError() << '\n';
    return;
  }

  SDL_RenderCopy(mRenderer, backgroundTexture, NULL, &destRect);
  SDL_RenderPresent(mRenderer);

  SDL_DestroyTexture(backgroundTexture);
}

void SDL_Handler::renderGame() {

  SDL_Rect destRect = {0, 0, CELL_WIDTH, CELL_WIDTH};
  SDL_RenderPresent(mRenderer);
}

SDL_Handler::SDL_Handler() {
  if (!init())
    SDL_cleanup();
}

SDL_Handler::~SDL_Handler() { SDL_cleanup(); }
