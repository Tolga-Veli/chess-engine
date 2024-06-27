#include "../include/SDL_Handler.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

bool SDL_Handler::init() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Unable to initialise SDL: " << SDL_GetError() << '\n';
    return false;
  }

  if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))) {
    std::cout << "Unable to initialise SDL_image: " << IMG_GetError() << '\n';
    return false;
  }

  window =
      SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr) {
    std::cout << "Unable to create window: " << SDL_GetError() << '\n';
    IMG_Quit();
    SDL_Quit();
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (renderer == nullptr) {
    std::cout << "Unable to create renderer: " << SDL_GetError() << '\n';
    IMG_Quit();
    SDL_Quit();
    return false;
  }

  surfaceScreen = IMG_Load("chessboard.png");
  if (surfaceScreen == nullptr) {
    std::cout << "Unable to load image: " << IMG_GetError() << '\n';
    IMG_Quit();
    SDL_Quit();
    return false;
  }

  convertFEN();
  return true;
}

void SDL_Handler::SDL_cleanup() {
  SDL_DestroyRenderer(renderer);
  SDL_FreeSurface(surfaceScreen);
  SDL_DestroyWindow(window);

  IMG_Quit();
  SDL_Quit();
}

SDL_Texture *SDL_Handler::loadImageFromFile(std::string path) {
  return SDL_CreateTextureFromSurface(renderer, IMG_Load(path.c_str()));
}

void SDL_Handler::renderChessboard(Game *game) {

  int windowWidth, windowHeight;
  SDL_GetWindowSize(window, &windowWidth, &windowHeight);

  // Set the destination rectangle to cover the entire window
  SDL_Rect destRect = {0, 0, windowWidth, windowHeight};

  SDL_Texture *textureScreen =
      SDL_CreateTextureFromSurface(renderer, surfaceScreen);
  if (textureScreen == nullptr) {
    std::cout << "textureScreen was a nullptr" << SDL_GetError() << '\n';
    return;
  }

  SDL_RenderCopy(renderer, textureScreen, NULL, &destRect);

  for (int i = 0; i < 64; i++) {
    renderPiece(i % 8, i / 8, game);
  }

  SDL_RenderPresent(renderer);
  SDL_DestroyTexture(textureScreen);
}

void SDL_Handler::selectPiece(int x, int y, Game *game) {
  if (game->selectedX == -1 || game->selectedY == -1)
    return;

  game->selectedX = x;
  game->selectedY = y;

  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, 100, 100};
  SDL_SetRenderDrawColor(renderer, 96, 96, 96, 50);
  SDL_RenderFillRect(renderer, &destRect);
  SDL_RenderPresent(renderer);
}

void SDL_Handler::movePiece(int x, int y, Game *game) {
  undoPiece(game->selectedX, game->selectedY, game);
  undoPiece(x, y, game);
  renderPiece(x, y, game);

  game->selectedX = -1;
  game->selectedY = -1;
}

void SDL_Handler::renderPiece(int x, int y, Game *game) {
  std::string image_path = "";
  std::string chess_piece = "";

  chess_piece = game->getPiece(x, y);
  if (chess_piece != ".")
    image_path = chess_piece + ".png";
  else
    return;

  if (image_path.size() < 2)
    return;

  SDL_Texture *texturePiece = loadImageFromFile(image_path);
  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, 100, 100};
  SDL_RenderCopy(renderer, texturePiece, NULL, &destRect);

  SDL_RenderPresent(renderer);

  SDL_DestroyTexture(texturePiece);
}

void SDL_Handler::undoPiece(int x, int y, Game *game) {

  game->changePiece(x, y);

  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, 100, 100};

  if ((x + y) % 2)
    SDL_SetRenderDrawColor(renderer, 209, 139, 71, 255);
  else
    SDL_SetRenderDrawColor(renderer, 255, 206, 158, 255);

  SDL_RenderFillRect(renderer, &destRect);
  SDL_RenderPresent(renderer);
}

SDL_Handler::SDL_Handler() { init(); }

SDL_Handler::~SDL_Handler() { SDL_cleanup(); }
