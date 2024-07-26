#include "../include/SDL_Handler.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>
#include <utility>

bool SDL_Handler::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Unable to initialise SDL: " << SDL_GetError() << '\n';
    return false;
  }
  if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))) {
    std::cout << "Unable to initialise SDL_image: " << IMG_GetError() << '\n';
    return false;
  }

  mWindow =
      SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE);

  if (mWindow == nullptr) {
    std::cout << "Unable to create window: " << SDL_GetError() << '\n';
    return false;
  }
  if (mRenderer == nullptr) {
    std::cout << "Unable to create renderer: " << SDL_GetError() << '\n';
    return false;
  }

  textures["WhitePawn"] = loadTextureFromFile("WhitePawn.png");
  textures["WhiteKnight"] = loadTextureFromFile("WhiteKnight.png");
  textures["WhiteBishop"] = loadTextureFromFile("WhiteBishop.png");
  textures["WhiteRook"] = loadTextureFromFile("WhiteRook.png");
  textures["WhiteQueen"] = loadTextureFromFile("WhiteQueen.png");
  textures["WhiteKing"] = loadTextureFromFile("WhiteKing.png");

  textures["BlackPawn"] = loadTextureFromFile("BlackPawn.png");
  textures["BlackKnight"] = loadTextureFromFile("BlackKnight.png");
  textures["BlackBishop"] = loadTextureFromFile("BlackBishop.png");
  textures["BlackRook"] = loadTextureFromFile("BlackRook.png");
  textures["BlackQueen"] = loadTextureFromFile("BlackQueen.png");
  textures["BlackKing"] = loadTextureFromFile("BlackKing.png");

  for (const auto &texture : textures) {
    if (texture.second == nullptr) {
      std::cout << "Failed to load texture for " << texture.first << ": "
                << SDL_GetError() << '\n';
      return false;
    }
  }

  return true;
}

void SDL_Handler::SDL_cleanup() {
  for (auto &nameTexture : textures) {
    SDL_DestroyTexture(nameTexture.second);
  }
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);

  IMG_Quit();
  SDL_Quit();
}

SDL_Texture *SDL_Handler::loadTextureFromFile(const std::string &path) {
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (surface == nullptr) {
    std::cout << "Unable to load image " << path << ": " << IMG_GetError()
              << '\n';
    return nullptr;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
  SDL_FreeSurface(surface);
  if (texture == nullptr) {
    std::cout << "Unable to create texture from " << path << ": "
              << SDL_GetError() << '\n';
  }
  return texture;
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

void SDL_Handler::renderPiece(const std::string &name, int x, int y) {
  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH};

  if (textures[name] == nullptr) {
    std::cout << "Texture not found for" << name << ": " << SDL_GetError()
              << '\n';
    return;
  }

  SDL_RenderCopy(mRenderer, textures[name], NULL, &destRect);
  SDL_RenderPresent(mRenderer);
}

void SDL_Handler::undoPiece(int x, int y) {
  // To implement undoPiece functionality, you need to redraw the specific cell
  // which was occupied by the piece. This might involve redrawing the cell
  // background and possibly other pieces.
  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH};
  if ((x + y) % 2)
    SDL_SetRenderDrawColor(mRenderer, 209, 139, 71,
                           255); // Assuming white background
  else
    SDL_SetRenderDrawColor(mRenderer, 255, 206, 158, 255);

  SDL_RenderFillRect(mRenderer, &destRect);
  SDL_RenderPresent(mRenderer);
}

SDL_Handler::SDL_Handler() {
  if (!init()) {
    SDL_cleanup();
    return;
  }
  renderChessboard();
}

SDL_Handler::~SDL_Handler() { SDL_cleanup(); }
