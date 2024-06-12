#include <utility>

#include "../include/Game.hpp"

bool Game::checkBitAtPos(std::string board, int index) {
  return (bitboards[board] & (1ULL << index)) != 0;
}

void Game::reverseBitAtPos(std::string board, int index) {
  bitboards[board] ^= (1 << index);
}

void Game::setzeroBitAtPos(std::string board, int index) {
  bitboards[board] &= ~(1ULL << index);
}

void Game::setoneBitAtPos(std::string board, int index) {
  bitboards[board] |= (1ULL << index);
}

std::string Game::getPiece(int x, int y) {
  for (std::pair<std::string, ull> name_bitboard : bitboards) {
    if (checkBitAtPos(name_bitboard.first, y * 8 + x))
      return name_bitboard.first;
  }
  return ".";
}

void Game::changePiece(int x, int y) {
  reverseBitAtPos(getPiece(x, y) + ".png", y * 8 + x);
}

void Game::init() {
  convertFEN();
  bitboards["WhitePawns"] = 0ULL;
  bitboards["BlackPawns"] = 0ULL;
  bitboards["WhiteRooks"] = 0ULL;
  bitboards["BlackRooks"] = 0ULL;
  bitboards["WhiteKnights"] = 0ULL;
  bitboards["BlackKnights"] = 0ULL;
  bitboards["WhiteBishops"] = 0ULL;
  bitboards["BlackBishops"] = 0ULL;
  bitboards["WhiteQueens"] = 0ULL;
  bitboards["BlackQueens"] = 0ULL;
  bitboards["WhiteKing"] = 0ULL;
  bitboards["BlackKing"] = 0ULL;

  for (int i = 0; i < 64; i++) {
    switch (board[i]) {
    case 'P':
      setoneBitAtPos("WhitePawns", i);
      break;
    case 'p':
      setoneBitAtPos("BlackPawns", i);
      break;
    case 'R':
      setoneBitAtPos("WhiteRooks", i);
      break;
    case 'r':
      setoneBitAtPos("BlackRooks", i);
      break;
    case 'N':
      setoneBitAtPos("WhiteKnights", i);
      break;
    case 'n':
      setoneBitAtPos("BlackKnights", i);
      break;
    case 'B':
      setoneBitAtPos("WhiteBishops", i);
      break;
    case 'b':
      setoneBitAtPos("BlackBishops", i);
      break;
    case 'Q':
      setoneBitAtPos("WhiteQueens", i);
      break;
    case 'q':
      setoneBitAtPos("BlackQueens", i);
      break;
    case 'K':
      setoneBitAtPos("WhiteKing", i);
      break;
    case 'k':
      setoneBitAtPos("BlackKing", i);
      break;
    default:
      break;
    }
  }
}

Game::Game() { init(); }
