#pragma once
#include <string>

class FEN {
private:
  const std::string input;
  void convertFEN();

public:
  // Capital letters - white, small letters - black
  static char board[64];
  // K-0, Q-1, k-2, q-3
  static bool castle[4];
  static int en_passant;
  static bool white_turn;

  FEN() : input("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {
    convertFEN();
  }

  FEN(const std::string game_string) : input(game_string) { convertFEN(); }

}; // namespace FEN
