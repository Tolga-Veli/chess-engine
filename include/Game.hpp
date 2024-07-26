#pragma once
#include "SDL_Handler.hpp"
#include "fen.hpp"
#define ull unsigned long long

class Game : public FEN {
private:
  // white: pawn-0, knight-1, bishop-2, rook-3, queen-4, king-5
  // black: pawn-6, knight-7, bishop-8, rook-9, queen-10, king-11

  std::map<std::string, ull> bitboards;

  bool checkBitAtPos(std::string name, int boardPos);
  void reverseBitAtPos(std::string name, int boardPos);
  void setzeroBitAtPos(std::string name, int boardPos);
  void setoneBitAtPos(std::string name, int boardPos);

public:
  void renderGame(SDL_Handler &handler);

  Game();
  ~Game();
};
