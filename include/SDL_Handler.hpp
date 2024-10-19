#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <unordered_map>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define CELL_WIDTH 100

// All enum values used to access bitboards using the hash table
enum bitboard_strings {
  Empty = 0,
  WhitePawn = 1,
  WhiteKnight,
  WhiteBishop,
  WhiteRook,
  WhiteQueen,
  WhiteKing,
  BlackPawn = 7,
  BlackKnight,
  BlackBishop,
  BlackRook,
  BlackQueen,
  BlackKing
};

class SDL_Handler {
private:
  // Window ptr
  static SDL_Window *m_window;

  // Renderer ptr
  static SDL_Renderer *m_renderer;

  // Hash table that holds the textures
  static std::unordered_map<bitboard_strings, SDL_Texture *> textures;

private:
  // Initializes and bootstraps SDL_Handler
  // SDL_Init, IMG_Init and the ptr for the window and renderer
  // are created here
  bool init();

  static SDL_Texture *load_texture_from_file(const std::string &path);

public:
  SDL_Event event;
  bool failed = false;

public:
  // If init() failes, the destructor is called prematurely and the program is
  // terminated
  SDL_Handler();

  // Frees the dynamically allocated memory
  static void SDL_cleanup();

  // calls SDL_cleanup
  ~SDL_Handler();

  void present_renderer();
  static void highlight_cell(int x, int y);
  static void render_chessboard();
  static void render_piece(const bitboard_strings name, int x, int y);
  static void undo_piece(int x, int y);
};
