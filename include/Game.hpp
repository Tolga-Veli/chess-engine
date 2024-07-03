#pragma once
#include "SDL_Handler.hpp"
#define ull unsigned long long

class Game : public SDL_Handler {
private:
  // white: pawn-0, knight-1, bishop-2, rook-3, queen-4, king-5
  // black: pawn-6, knight-7, bishop-8, rook-9, queen-10, king-11

  ull bitboards[12];

  bool checkBitAtPos(int boardIndex, int boardPos);
  void reverseBitAtPos(int boardIndex, int boardPos);
  void setzeroBitAtPos(int boardIndex, int boardPos);
  void setoneBitAtPos(int boardIndex, int boardPos);

public:
  Game();
  ~Game();
};
