#include "../include/Game.hpp"
void Game::init() {
  convertFEN();
  for (int i = 0; i < 12; i++) {
    bitboard_piece[i] = 0ULL;
  }

  // 0-white pawns, 1-black pawns, 2-white rooks, 3-black rooks, 4-white
  // knights, 5-black knights, 6-white bishops, 7-black bishops, 8-white queens,
  // 9-black queens, 10-white king, 11-black king
  for (int i = 0; i < 64; i++) {
    switch (board[i]) {
    case 'P':
      setoneBitAtPos(0, i);
      break;
    case 'p':
      setoneBitAtPos(1, i);
      break;
    case 'R':
      setoneBitAtPos(2, i);
      break;
    case 'r':
      setoneBitAtPos(3, i);
      break;
    case 'N':
      setoneBitAtPos(4, i);
      break;
    case 'n':
      setoneBitAtPos(5, i);
      break;
    case 'B':
      setoneBitAtPos(6, i);
      break;
    case 'b':
      setoneBitAtPos(7, i);
      break;
    case 'Q':
      setoneBitAtPos(8, i);
      break;
    case 'q':
      setoneBitAtPos(9, i);
      break;
    case 'K':
      setoneBitAtPos(10, i);
      break;
    case 'k':
      setoneBitAtPos(11, i);
      break;
    default:
      break;
    }
  }
}

void Game::setzeroBitAtPos(int bitboardIndex, int index) {
  bitboard_piece[bitboardIndex] &= ~(1ULL << index);
}

void Game::setoneBitAtPos(int bitboardIndex, int index) {
  bitboard_piece[bitboardIndex] |= (1ULL << index);
}

bool Game::checkBitAtPos(int bitboardIndex, int index) {
  ull mask = 1ULL << index;

  // Perform bitwise AND operation with the mask
  // If the result is non-zero, the bit at bitIndex is set
  return (bitboard_piece[bitboardIndex] & mask) != 0;
}

char Game::getPiece(int x, int y) {
  for (int i = 0; i < 12; i++) {
    if (checkBitAtPos(i, y * 8 + x)) {
      switch (i) {
      case 0:
        return 'P';
      case 1:
        return 'p';
      case 2:
        return 'R';
      case 3:
        return 'r';
      case 4:
        return 'N';
      case 5:
        return 'n';
      case 6:
        return 'B';
      case 7:
        return 'b';
      case 8:
        return 'Q';
      case 9:
        return 'q';
      case 10:
        return 'K';
      case 11:
        return 'k';
      }
    }
  }

  return '.';
}

bool Game::selectPiece(int x, int y) {

  if (getPiece(x, y) != '.') {
    selectedX = x;
    selectedY = y;
    return true;
  }

  return false;
}
Game::Game() { init(); }
