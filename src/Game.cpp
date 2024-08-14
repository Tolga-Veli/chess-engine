#include "../include/Game.hpp"
#include "../include/fen.hpp"
#include <SDL2/SDL_render.h>
#include <cctype>
#include <iostream>

// Bitwise operations for the bitboards
bool Game::checkBitAtPos(const ull &bitboard, int boardPos) const {
  return (bitboard & (1ULL << boardPos)) != 0;
}

void Game::reverseBitAtPos(ull &bitboard, int boardPos) {
  bitboard ^= (1ULL << boardPos);
}

void Game::setzeroBitAtPos(ull &bitboard, int boardPos) {
  bitboard &= ~(1ULL << boardPos);
}

void Game::setoneBitAtPos(ull &bitboard, int boardPos) {
  bitboard |= (1ULL << boardPos);
}

Game::Game(SDL_Handler &handler) : m_handler(&handler) {
  // intialise bitboards
  bitboards["WhitePawn"] = 0ULL;
  bitboards["WhiteKnight"] = 0ULL;
  bitboards["WhiteBishop"] = 0ULL;
  bitboards["WhiteRook"] = 0ULL;
  bitboards["WhiteQueen"] = 0ULL;
  bitboards["WhiteKing"] = 0ULL;
  bitboards["BlackPawn"] = 0ULL;
  bitboards["BlackKnight"] = 0ULL;
  bitboards["BlackBishop"] = 0ULL;
  bitboards["BlackRook"] = 0ULL;
  bitboards["BlackQueen"] = 0ULL;
  bitboards["BlackKing"] = 0ULL;

  white_bitboard = 0ULL;
  black_bitboard = 0ULL;

  // covert fen string to values in the bitboards
  FEN startstring;

  for (int i = 0; i < 4; i++)
    castle[i] = startstring.f_board[i];
  enPassant = startstring.f_enPassant;
  whiteTurn = startstring.f_whiteTurn;

  for (int i = 0; i < 64; i++) {
    switch (startstring.f_board[i]) {
    case 'P':
      setoneBitAtPos(bitboards["WhitePawn"], i);
      break;
    case 'p':
      setoneBitAtPos(bitboards["BlackPawn"], i);
      break;
    case 'R':
      setoneBitAtPos(bitboards["WhiteRook"], i);
      break;
    case 'r':
      setoneBitAtPos(bitboards["BlackRook"], i);
      break;
    case 'N':
      setoneBitAtPos(bitboards["WhiteKnight"], i);
      break;
    case 'n':
      setoneBitAtPos(bitboards["BlackKnight"], i);
      break;
    case 'B':
      setoneBitAtPos(bitboards["WhiteBishop"], i);
      break;
    case 'b':
      setoneBitAtPos(bitboards["BlackBishop"], i);
      break;
    case 'Q':
      setoneBitAtPos(bitboards["WhiteQueen"], i);
      break;
    case 'q':
      setoneBitAtPos(bitboards["BlackQueen"], i);
      break;
    case 'K':
      setoneBitAtPos(bitboards["WhiteKing"], i);
      break;
    case 'k':
      setoneBitAtPos(bitboards["BlackKing"], i);
      break;
    default:
      break;
    }
  }

  // render pieces on board
  for (auto &bitboard : bitboards) {
    if (bitboard.first[0] == 'W')
      white_bitboard |= bitboard.second;
    else
      black_bitboard |= bitboard.second;
    for (int i = 0; i < 64; i++) {
      if (checkBitAtPos(bitboard.second, i))
        m_handler->renderPiece(bitboard.first, i % 8, i / 8);
    }
  }
  allineone_bitboard = white_bitboard | black_bitboard;
  pieceSelected = false;
}

Game::~Game() { m_handler = nullptr; }

void Game::selectPiece(int index) {
  for (auto &bitboard : bitboards) {
    bool currTurn = bitboard.first[0] == 'W' ? true : false;
    std::cout << (currTurn ? "white\n" : "black\n");
    std::cout << bitboard.first << " " << (whiteTurn ? "white\n" : "black\n");
    if (checkBitAtPos(bitboard.second, index) && currTurn == whiteTurn) {
      selectedPiece = {bitboard.first, index};
      pieceSelected = true;
      break;
    }
  }
  if (pieceSelected == true) {
    m_handler->highlightSquare(index % 8, index / 8);
    highlightLegalMoves();
  }
}

void Game::movePiece(int index) {
  ull legalMoves = getLegalMoves();
  if (pieceSelected && checkBitAtPos(legalMoves, index)) {
    setzeroBitAtPos(bitboards[selectedPiece.first], selectedPiece.second);

    for (auto &bitboard : bitboards) {
      if (checkBitAtPos(bitboard.second, index))
        setzeroBitAtPos(bitboard.second, index);
    }
    setoneBitAtPos(bitboards[selectedPiece.first], index);

    for (int i = 0; i < 64; i++)
      m_handler->undoPiece(i % 8, i / 8);

    for (auto &bitboard : bitboards) {
      for (int i = 0; i < 64; i++) {
        if (checkBitAtPos(bitboards[bitboard.first], i))
          m_handler->renderPiece(bitboard.first, i % 8, i / 8);
      }
    }
    selectedPiece = {"", -1};
    pieceSelected = false;
    whiteTurn = !whiteTurn;
  }
}

void Game::highlightLegalMoves() {
  ull legalMovesBoard = getLegalMoves();
  for (int i = 0; i < 64; i++) {
    if (checkBitAtPos(legalMovesBoard, i)) {
      m_handler->undoPiece(i % 8, i / 8);
      m_handler->highlightSquare(i % 8, i / 8);
      if (checkBitAtPos(allineone_bitboard, i))
        for (auto &bitboard : bitboards) {
          if (checkBitAtPos(bitboard.second, i))
            m_handler->renderPiece(bitboard.first, i % 8, i / 8);
        }
    }
  }
}

ull Game::getPawnMoves() {
  ull legalPawnMoves = 0ULL;
  int direction = whiteTurn ? -1 : 1;

  int moves[3] = {7, 8, 9};

  for (int move : moves) {
    int arrIndex = selectedPiece.second + move * direction;
    if (arrIndex < 0 || arrIndex > 63)
      continue;
    if (move == 8 && !checkBitAtPos(allineone_bitboard, arrIndex)) {
      setoneBitAtPos(legalPawnMoves, arrIndex);
      if (selectedPiece.second / 8 == 1 || selectedPiece.second / 8 == 6)
        setoneBitAtPos(legalPawnMoves, arrIndex + 8 * direction);
    }
    if (move == 7 &&
        checkBitAtPos(whiteTurn ? black_bitboard : white_bitboard, arrIndex))
      setoneBitAtPos(legalPawnMoves, arrIndex);
  }
  return legalPawnMoves;
}

ull Game::getKnightMoves() {
  ull legalKnightMoves = 0ULL;
  int moves[8] = {-17, -15, -10, -6, 6, 10, 15, 17};

  for (int move : moves) {
    int arrIndex = selectedPiece.second + move;
    if (arrIndex >= 0 && arrIndex < 64 &&
        ((arrIndex % 8) - (selectedPiece.second % 8) >= -2 &&
         (arrIndex % 8) - (selectedPiece.second % 8) <=
             2) && // Ensure move stays within board boundaries
        !checkBitAtPos(whiteTurn ? white_bitboard : black_bitboard, arrIndex)) {
      setoneBitAtPos(legalKnightMoves, arrIndex);
    }
  }

  return legalKnightMoves;
}

ull Game::getDiagonalMoves() {
  ull legalDiagonalMoves = 0ULL;
  int moves[4] = {-9, -7, 7, 9};

  for (int move : moves) {
    int arrIndex = selectedPiece.second;
    while (true) {
      arrIndex += move;
      if (arrIndex < 0 || arrIndex >= 64 ||
          ((move == -9 || move == 7) && (arrIndex % 8 == 7)) ||
          ((move == -7 || move == 9) && (arrIndex % 8 == 0)))
        break; // Boundary check

      if (checkBitAtPos(whiteTurn ? white_bitboard : black_bitboard, arrIndex))
        break;
      setoneBitAtPos(legalDiagonalMoves, arrIndex);
      if (checkBitAtPos(whiteTurn ? black_bitboard : white_bitboard, arrIndex))
        break;
    }
  }

  return legalDiagonalMoves;
}

ull Game::getRookMoves() {
  ull legalRookMoves = 0ULL;
  int moves[4] = {-8, -1, 1, 8};

  for (int move : moves) {
    int arrIndex = selectedPiece.second;
    while (true) {
      arrIndex += move;
      if (arrIndex < 0 || arrIndex >= 64 || (move == -1 && arrIndex % 8 == 7) ||
          (move == 1 && arrIndex % 8 == 0))
        break; // Boundary check

      if (checkBitAtPos(whiteTurn ? white_bitboard : black_bitboard, arrIndex))
        break;
      setoneBitAtPos(legalRookMoves, arrIndex);
      if (checkBitAtPos(whiteTurn ? black_bitboard : white_bitboard, arrIndex))
        break;
    }
  }

  return legalRookMoves;
}

ull Game::getKingMoves() {
  ull legalKingMoves = 0ULL;
  int moves[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

  for (int move : moves) {
    int arrIndex = selectedPiece.second + move;
    if (arrIndex >= 0 && arrIndex < 64 &&
        ((arrIndex % 8) - (selectedPiece.second % 8) >= -1 &&
         (arrIndex % 8) - (selectedPiece.second % 8) <=
             1) && // Ensure move stays within board boundaries
        !checkBitAtPos(whiteTurn ? white_bitboard : black_bitboard, arrIndex)) {
      setoneBitAtPos(legalKingMoves, arrIndex);
    }
  }

  // Castling (simplified, should be expanded to include checks for castling
  // rights and conditions)
  if (whiteTurn && (castle[0] || castle[1])) {
    if (castle[0] && !(allineone_bitboard & 0b110ULL)) { // White kingside
      setoneBitAtPos(legalKingMoves, selectedPiece.second + 2);
    }
    if (castle[1] && !(allineone_bitboard & 0b1111000ULL)) { // White queenside
      setoneBitAtPos(legalKingMoves, selectedPiece.second - 2);
    }
  } else if (!whiteTurn && (castle[2] || castle[3])) {
    if (castle[2] &&
        !(allineone_bitboard & (0b110ULL << 56))) { // Black kingside
      setoneBitAtPos(legalKingMoves, selectedPiece.second + 2);
    }
    if (castle[3] &&
        !(allineone_bitboard & (0b1111000ULL << 56))) { // Black queenside
      setoneBitAtPos(legalKingMoves, selectedPiece.second - 2);
    }
  }

  return legalKingMoves;
}

ull Game::getLegalMoves() {
  switch (toupper(selectedPiece.first[5])) {
  case 'P':
    return getPawnMoves();
  case 'N':
    return getKnightMoves();
  case 'B':
    return getDiagonalMoves();
  case 'R':
    return getRookMoves();
  case 'Q':
    return getRookMoves() | getDiagonalMoves();
  case 'K':
    return getKingMoves();
  default:
    return 0ULL;
  }
}
