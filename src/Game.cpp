#include "Game.hpp"

void Game::init() {
  // 0-white pawns, 1-black pawns, 2-white rooks, 3-black rooks, 4-white
  // knights, 5-black knights, 6-white bishops, 7-black bishops, 8-white queens,
  // 9-black queens, 10-white king, 11-black king
  for (int i = 0; i < 64; i++) {
    switch (board[i]) {
    case 'r':
      setoneBitAtPos(bitboard_piece[3], i);
      break;
    case 'n':
      setoneBitAtPos(bitboard_piece[5], i);
      break;
    case 'b':
      setoneBitAtPos(bitboard_piece[7], i);
      break;
    case 'q':
      setoneBitAtPos(bitboard_piece[9], i);
      break;
    case 'k':
      setoneBitAtPos(bitboard_piece[11], i);
      break;
    case 'p':
      setoneBitAtPos(bitboard_piece[1], i);
      break;
    case 'R':
      setoneBitAtPos(bitboard_piece[2], i);
      break;
    case 'N':
      setoneBitAtPos(bitboard_piece[4], i);
      break;
    case 'B':
      setoneBitAtPos(bitboard_piece[6], i);
      break;
    case 'Q':
      setoneBitAtPos(bitboard_piece[8], i);
      break;
    case 'K':
      setoneBitAtPos(bitboard_piece[10], i);
      break;
    case 'P':
      setoneBitAtPos(bitboard_piece[0], i);
      break;
    default:
      break;
    }
  }
}

void Game::setzeroBitAtPos(unsigned long long bitboard, int index) {
  bitboard_piece[bitboard] ^= (unsigned long long)1 << index;
}

void Game::setoneBitAtPos(unsigned long long bitboard, int index) {
  bitboard_piece[bitboard] = bitboard | (unsigned long long)1 << index;
}

bool Game::checkBitAtPos(unsigned long long bitboard, int index) {
  unsigned long long mask = 1ULL << index;

  // Perform bitwise AND operation with the mask
  // If the result is non-zero, the bit at bitIndex is set
  return (bitboard & mask) != 0;
}

Game::Game() { init(); }

Game::~Game() {}
