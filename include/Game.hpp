#pragma once
#include "fen.hpp"
#define ull unsigned long long

class Game : FEN {
private:
  // 0-white pawns, 1-black pawns, 2-white rooks, 3-black rooks, 4-white
  // knights, 5-black knights, 6-white bishops, 7-black bishops, 8-white queens,
  // 9-black queens, 10-white king, 11-black king
  ull bitboard_piece[12];

  bool checkBitAtPos(int bitboardIndex, int index);
  void setzeroBitAtPos(int bitboardIndex, int index);
  void setoneBitAtPos(int bitboardIndex, int index);

public:
  int selectedX = 0, selectedY = 0;
  bool pieceSelected = false;

  void init();
  char getPiece(int x, int y);
  bool selectPiece(int x, int y);

  Game();
};
