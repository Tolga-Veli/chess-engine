#include "../include/SDL_Handler.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>
#include <utility>

bool SDL_Handler::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Unable to initialise SDL: " << SDL_GetError() << '\n';
    return false;
  }
  if (!(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))) {
    std::cerr << "Unable to initialise SDL_image: " << IMG_GetError() << '\n';
    return false;
  }

  m_window =
      SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);

  if (m_window == nullptr) {
    std::cerr << "Unable to create window: " << SDL_GetError() << '\n';
    return false;
  }
  if (m_renderer == nullptr) {
    std::cerr << "Unable to create renderer: " << SDL_GetError() << '\n';
    return false;
  }

  textures[WhitePawn] = load_texture_from_file("WhitePawn.png");
  textures[WhiteKnight] = load_texture_from_file("WhiteKnight.png");
  textures[WhiteBishop] = load_texture_from_file("WhiteBishop.png");
  textures[WhiteRook] = load_texture_from_file("WhiteRook.png");
  textures[WhiteQueen] = load_texture_from_file("WhiteQueen.png");
  textures[WhiteKing] = load_texture_from_file("WhiteKing.png");

  textures[BlackPawn] = load_texture_from_file("BlackPawn.png");
  textures[BlackKnight] = load_texture_from_file("BlackKnight.png");
  textures[BlackBishop] = load_texture_from_file("BlackBishop.png");
  textures[BlackRook] = load_texture_from_file("BlackRook.png");
  textures[BlackQueen] = load_texture_from_file("BlackQueen.png");
  textures[BlackKing] = load_texture_from_file("BlackKing.png");

  for (const auto &texture : textures) {
    if (texture.second == nullptr) {
      std::cerr << "Failed to load texture for " << texture.first << ": "
                << SDL_GetError() << '\n';
      return false;
    }
  }

  render_chessboard();
  return true;
}

void SDL_Handler::SDL_cleanup() {
  for (auto &nameTexture : textures) {
    SDL_DestroyTexture(nameTexture.second);
  }

  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);

  IMG_Quit();
  SDL_Quit();
}

SDL_Handler::SDL_Handler() { failed = init(); }

SDL_Handler::~SDL_Handler() { SDL_cleanup(); }

SDL_Texture *SDL_Handler::load_texture_from_file(const std::string &path) {
  SDL_Surface *surface = IMG_Load(("../assets/" + path).c_str());
  if (surface == nullptr) {
    std::cerr << "Unable to load image " << path << ": " << IMG_GetError()
              << '\n';
    return nullptr;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  SDL_FreeSurface(surface);
  if (texture == nullptr) {
    std::cerr << "Unable to create texture from " << path << ": "
              << SDL_GetError() << '\n';
    return nullptr;
  }
  return texture;
}

void SDL_Handler::present_renderer() { SDL_RenderPresent(m_renderer); }

void SDL_Handler::render_chessboard() {
  // Set the destination rectangle to cover the entire window
  SDL_Rect destRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

  SDL_Texture *backgroundTexture =
      load_texture_from_file("../assets/chessboard.png");
  if (backgroundTexture == nullptr) {
    std::cerr << "textureScreen was a nullptr" << SDL_GetError() << '\n';
    SDL_cleanup();
    return;
  }

  SDL_RenderCopy(m_renderer, backgroundTexture, NULL, &destRect);
  SDL_DestroyTexture(backgroundTexture);
}

void SDL_Handler::render_piece(const bitboard_strings name, int x, int y) {
  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH};

  if (textures[name] == nullptr) {
    std::cerr << "Texture not found for " << name << ": " << SDL_GetError()
              << '\n';
    return;
  }

  SDL_RenderCopy(m_renderer, textures[name], NULL, &destRect);
}

void SDL_Handler::undo_piece(int x, int y) {
  // To implement undo_piece functionality, you need to redraw the specific cell
  // which was occupied by the piece. This might involve redrawing the cell
  // background and possibly other pieces.
  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH};
  if ((x + y) % 2)
    SDL_SetRenderDrawColor(m_renderer, 209, 139, 71, 255);
  else
    SDL_SetRenderDrawColor(m_renderer, 255, 206, 158, 255);

  SDL_RenderFillRect(m_renderer, &destRect);
}

void SDL_Handler::highlight_cell(int x, int y) {
  SDL_Rect destRect = {x * CELL_WIDTH, y * CELL_WIDTH, CELL_WIDTH, CELL_WIDTH};

  // Set the draw color with the desired transparency
  // RGBA values, where the last value is alpha (transparency)
  SDL_SetRenderDrawColor(m_renderer, 10, 10, 10,
                         150); // Adjust the alpha value as needed

  // Set the blend mode to blend to enable transparency
  SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);

  // Draw the rectangle with the current draw color
  SDL_RenderFillRect(m_renderer, &destRect);
  SDL_RenderPresent(m_renderer);
}
