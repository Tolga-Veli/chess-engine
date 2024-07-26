#include "../include/Game.hpp"

bool Game::checkBitAtPos(const std::string name, int boardPos) {
  return (bitboards[name] & (1ULL << boardPos)) != 0;
}

void Game::reverseBitAtPos(const std::string name, int boardPos) {
  bitboards[name] ^= (1ULL << boardPos);
}

void Game::setzeroBitAtPos(const std::string name, int boardPos) {
  bitboards[name] &= ~(1ULL << boardPos);
}

void Game::setoneBitAtPos(const std::string name, int boardPos) {
  bitboards[name] |= (1ULL << boardPos);
}

Game::Game() {

  // Initialize bitboards
  bitboards["WhitePawn"] = 0;
  bitboards["WhiteKnight"] = 0;
  bitboards["WhiteBishop"] = 0;
  bitboards["WhiteRook"] = 0;
  bitboards["WhiteQueen"] = 0;
  bitboards["WhiteKing"] = 0;
  bitboards["BlackPawn"] = 0;
  bitboards["BlackKnight"] = 0;
  bitboards["BlackBishop"] = 0;
  bitboards["BlackRook"] = 0;
  bitboards["BlackQueen"] = 0;
  bitboards["BlackKing"] = 0;
  convertFEN();

  for (int i = 0; i < 64; i++) {
    switch (board[i]) {
    case 'P':
      setoneBitAtPos("WhitePawn", i);
      break;
    case 'p':
      setoneBitAtPos("BlackPawn", i);
      break;
    case 'R':
      setoneBitAtPos("WhiteRook", i);
      break;
    case 'r':
      setoneBitAtPos("BlackRook", i);
      break;
    case 'N':
      setoneBitAtPos("WhiteKnight", i);
      break;
    case 'n':
      setoneBitAtPos("BlackKnight", i);
      break;
    case 'B':
      setoneBitAtPos("WhiteBishop", i);
      break;
    case 'b':
      setoneBitAtPos("BlackBishop", i);
      break;
    case 'Q':
      setoneBitAtPos("WhiteQueen", i);
      break;
    case 'q':
      setoneBitAtPos("BlackQueen", i);
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

void Game::renderGame(SDL_Handler &handler) {
  for (std::pair<std::string, ull> bitboard : bitboards) {
    for (int i = 0; i < 64; i++) {
      if (checkBitAtPos(bitboard.first, i))
        handler.renderPiece(bitboard.first, i % 8, i / 8);
    }
  }
}

Game::~Game() {}
