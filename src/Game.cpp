#include "../include/Game.hpp"

bool Game::checkBitAtPos(int boardIndex, int boardPos) {
  return (bitboards[boardIndex] & (1ULL << boardPos)) != 0;
}

void Game::reverseBitAtPos(int boardIndex, int boardPos) {
  bitboards[boardIndex] ^= (1 << boardPos);
}

void Game::setzeroBitAtPos(int boardIndex, int boardPos) {
  bitboards[boardIndex] &= ~(1ULL << boardPos);
}

void Game::setoneBitAtPos(int boardIndex, int boardPos) {
  bitboards[boardIndex] |= (1ULL << boardPos);
}

Game::Game(SDL_Handler &handler) {
  // white: pawn-0, knight-1, bishop-2, rook-3, queen-4, king-5
  // black: pawn-6, knight-7, bishop-8, rook-9, queen-10, king-11
  convertFEN();

  for (int i = 0; i < 64; i++) {
    switch (board[i]) {
    case 'P':
      setoneBitAtPos(0, i);
      break;
    case 'p':
      setoneBitAtPos(6, i);
      break;
    case 'R':
      setoneBitAtPos(3, i);
      break;
    case 'r':
      setoneBitAtPos(9, i);
      break;
    case 'N':
      setoneBitAtPos(1, i);
      break;
    case 'n':
      setoneBitAtPos(7, i);
      break;
    case 'B':
      setoneBitAtPos(2, i);
      break;
    case 'b':
      setoneBitAtPos(8, i);
      break;
    case 'Q':
      setoneBitAtPos(4, i);
      break;
    case 'q':
      setoneBitAtPos(10, i);
      break;
    case 'K':
      setoneBitAtPos(5, i);
      break;
    case 'k':
      setoneBitAtPos(11, i);
      break;
    default:
      break;
    }
  }
}
