#pragma once
#include "SDL_Handler.hpp"
#include <unordered_map>
#include <utility>
#define ull unsigned long long

class Game {
private:
  SDL_Handler *m_handler;

  std::unordered_map<std::string, ull> bitboards;
  ull white_bitboard;
  ull black_bitboard;
  ull allineone_bitboard;

  bool checkBitAtPos(const ull &bitboard, int boardPos) const;
  void reverseBitAtPos(ull &bitboard, int boardPos);
  void setzeroBitAtPos(ull &bitboard, int boardPos);
  void setoneBitAtPos(ull &bitboard, int boardPos);

public:
  bool pieceSelected;
  // K-0, Q-1, k-2, q-3
  // 0 -> 7, 8 -> 15, -1 -> noEnPassant
  bool castle[4];
  int enPassant;
  bool whiteTurn;

  std::pair<std::string, int> selectedPiece;

  Game(SDL_Handler &handler);
  ~Game();

  void GameLoop();
  void selectPiece(int index);
  void movePiece(int index);
  void highlightLegalMoves();

  ull getLegalMoves();
  ull getPawnMoves();
  ull getKnightMoves();
  ull getDiagonalMoves();
  ull getRookMoves();
  ull getKingMoves();
};
