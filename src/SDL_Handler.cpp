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

  SDL_FreeSurface(surfaceScreen);
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

void SDL_Handler::renderPiece(int x, int y, Game *game) {

  if (game->pieceSelected) {
    undoPieceRender(game->selectedX, game->selectedY);
    game->pieceSelected = false;
  }

  std::string image_path = "";
  switch (game->getPiece(x, y)) {
  case 'r':
    image_path = "BlackRook.png";
    break;
  case 'n':
    image_path = "BlackKnight.png";
    break;
  case 'b':
    image_path = "BlackBishop.png";
    break;
  case 'q':
    image_path = "BlackQueen.png";
    break;
  case 'k':
    image_path = "BlackKing.png";
    break;
  case 'p':
    image_path = "BlackPawn.png";
    break;
  case 'R':
    image_path = "WhiteRook.png";
    break;
  case 'N':
    image_path = "WhiteKnight.png";
    break;
  case 'B':
    image_path = "WhiteBishop.png";
    break;
  case 'Q':
    image_path = "WhiteQueen.png";
    break;
  case 'K':
    image_path = "WhiteKing.png";
    break;
  case 'P':
    image_path = "WhitePawn.png";
    break;
  default:
    break;
  }

  if (image_path.size() < 2)
    return;

  SDL_Texture *texturePiece = loadImageFromFile(image_path);
  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, 100, 100};
  SDL_RenderCopy(renderer, texturePiece, NULL, &destRect);

  SDL_RenderPresent(renderer);

  SDL_DestroyTexture(texturePiece);
}

void SDL_Handler::undoPieceRender(int x, int y) {
  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, 100, 100};

  if ((x + y) % 2)
    SDL_SetRenderDrawColor(renderer, 209, 139, 71, 255);
  else
    SDL_SetRenderDrawColor(renderer, 255, 206, 158, 255);

  SDL_RenderFillRect(renderer, &destRect);
  SDL_RenderPresent(renderer);
}

void SDL_Handler::selectPieceGraphics(int x, int y) {
  undoPieceRender(x, y);

  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, 100, 100};

  if ((x + y) % 2)
    SDL_SetRenderDrawColor(renderer, 3, 169, 252, 50);
  else
    SDL_SetRenderDrawColor(renderer, 3, 169, 252, 120);

  SDL_RenderFillRect(renderer, &destRect);
  SDL_RenderPresent(renderer);
}

SDL_Handler::SDL_Handler() { init(); }

SDL_Handler::~SDL_Handler() { SDL_cleanup(); }
