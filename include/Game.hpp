#pragma once
#include "fen.hpp"
#include <map>

#define ull unsigned long long

class Game : FEN {
private:
  std::map<std::string, ull> bitboards;

  bool checkBitAtPos(std::string board, int index);
  void reverseBitAtPos(std::string board, int index);
  void setzeroBitAtPos(std::string board, int index);
  void setoneBitAtPos(std::string board, int index);

public:
  int selectedX = 0, selectedY = 0;

  Game();
  ~Game();

  std::string getPiece(int x, int y);
  void changePiece(int x, int y);
};
