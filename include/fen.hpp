#pragma once
#include <string>

class FEN {
private:
  std::string input =
      "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

public:
  // Capital letters - white, small letters - black
  char board[64];
  // K-0, Q-1, k-2, q-3
  bool castle[4];
  int enPassant;
  bool whiteTurn;

  void convertFEN();
};
