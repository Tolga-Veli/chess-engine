#pragma once
#include "fen.hpp"

class Game : FEN {
private:
public:
  // 0-white pawns, 1-black pawns, 2-white rooks, 3-black rooks, 4-white
  // knights, 5-black knights, 6-white bishops, 7-black bishops, 8-white queens,
  // 9-black queens, 10-white king, 11-black king
  unsigned long long bitboard_piece[12];

  void init();

  bool checkBitAtPos(unsigned long long bitboard, int index);
  void setzeroBitAtPos(unsigned long long bitboard, int index);
  void setoneBitAtPos(unsigned long long bitboard, int index);

  Game();
  ~Game();
};
