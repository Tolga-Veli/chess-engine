#pragma once
#include <string>

class FEN {
private:
  const std::string input =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
  void convertFEN();

public:
  // Capital letters - white, small letters - black
  char f_board[64];
  // K-0, Q-1, k-2, q-3
  bool f_castle[4];
  int f_enPassant;
  bool f_whiteTurn;

  FEN();
};
