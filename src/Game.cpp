#include "../include/Game.hpp"
#include "../include/fen.hpp"
#include <SDL2/SDL_render.h>

// Bitwise operations for the bitboards

bool Game::check_bit(const ull &bitboard, int boardPos) const {
  return (bitboard & (1ULL << boardPos)) != 0;
}

void Game::reverse_bit(ull &bitboard, int boardPos) {
  bitboard ^= (1ULL << boardPos);
}

void Game::clear_bit(ull &bitboard, int boardPos) {
  bitboard &= ~(1ULL << boardPos);
}

void Game::set_bit(ull &bitboard, int boardPos) {
  bitboard |= (1ULL << boardPos);
}

Game::Game() {
  // intialise bitboards
  bitboards[WhitePawn] = 0ULL;
  bitboards[WhiteKnight] = 0ULL;
  bitboards[WhiteBishop] = 0ULL;
  bitboards[WhiteRook] = 0ULL;
  bitboards[WhiteQueen] = 0ULL;
  bitboards[WhiteKing] = 0ULL;
  bitboards[BlackPawn] = 0ULL;
  bitboards[BlackKnight] = 0ULL;
  bitboards[BlackBishop] = 0ULL;
  bitboards[BlackRook] = 0ULL;
  bitboards[BlackQueen] = 0ULL;
  bitboards[BlackKing] = 0ULL;

  white_bitboard = 0ULL;
  black_bitboard = 0ULL;

  // covert fen string to values in the bitboards
  FEN startstring;

  for (int i = 0; i < 4; i++)
    castle[i] = startstring.board[i];
  en_passant = startstring.en_passant;
  white_turn = startstring.white_turn;

  for (int i = 0; i < 64; i++) {
    switch (startstring.board[i]) {
    case 'P':
      set_bit(bitboards[WhitePawn], i);
      break;
    case 'p':
      set_bit(bitboards[BlackPawn], i);
      break;
    case 'R':
      set_bit(bitboards[WhiteRook], i);
      break;
    case 'r':
      set_bit(bitboards[BlackRook], i);
      break;
    case 'N':
      set_bit(bitboards[WhiteKnight], i);
      break;
    case 'n':
      set_bit(bitboards[BlackKnight], i);
      break;
    case 'B':
      set_bit(bitboards[WhiteBishop], i);
      break;
    case 'b':
      set_bit(bitboards[BlackBishop], i);
      break;
    case 'Q':
      set_bit(bitboards[WhiteQueen], i);
      break;
    case 'q':
      set_bit(bitboards[BlackQueen], i);
      break;
    case 'K':
      set_bit(bitboards[WhiteKing], i);
      break;
    case 'k':
      set_bit(bitboards[BlackKing], i);
      break;
    default:
      break;
    }
  }

  // render pieces on board
  for (auto &bitboard : bitboards) {
    if (bitboard.first < 7) // BlackPawn = 7, everything white < 7
      white_bitboard |= bitboard.second;
    else
      black_bitboard |= bitboard.second;
    for (int i = 0; i < 64; i++) {
      if (check_bit(bitboard.second, i))
        SDL_Handler::render_piece(bitboard.first, i % 8, i / 8);
    }
  }
  allineone_bitboard = white_bitboard | black_bitboard;
  piece_selected = false;
}

void Game::select_piece(int index) {
  for (auto &bitboard : bitboards) {
    bool currTurn = bitboard.first < 7 ? true : false;
    if (check_bit(bitboard.second, index) && currTurn == white_turn) {
      selectedPiece = {bitboard.first, index};
      piece_selected = true;
      break;
    }
  }
  if (piece_selected == true) {
    SDL_Handler::highlight_cell(index % 8, index / 8);
    highlight_legal_moves();
  }
}

void Game::move_piece(int index) {
  ull legalMoves = get_legal_moves();
  if (piece_selected && check_bit(legalMoves, index)) {
    clear_bit(bitboards[selectedPiece.first], selectedPiece.second);

    for (auto &bitboard : bitboards) {
      if (check_bit(bitboard.second, index))
        clear_bit(bitboard.second, index);
    }
    set_bit(bitboards[selectedPiece.first], index);

    for (int i = 0; i < 64; i++)
      SDL_Handler::undo_piece(i % 8, i / 8);

    for (auto &bitboard : bitboards) {
      for (int i = 0; i < 64; i++) {
        if (check_bit(bitboards[bitboard.first], i))
          SDL_Handler::render_piece(bitboard.first, i % 8, i / 8);
      }
    }
    selectedPiece = {Empty, -1};
    piece_selected = false;
    white_turn = !white_turn;
  }
}

void Game::highlight_legal_moves() {
  ull legalMovesBoard = get_legal_moves();
  for (int i = 0; i < 64; i++) {
    if (check_bit(legalMovesBoard, i)) {
      SDL_Handler::undo_piece(i % 8, i / 8);
      SDL_Handler::highlight_cell(i % 8, i / 8);
      if (check_bit(allineone_bitboard, i))
        for (auto &bitboard : bitboards) {
          if (check_bit(bitboard.second, i))
            SDL_Handler::render_piece(bitboard.first, i % 8, i / 8);
        }
    }
  }
}

ull Game::get_legal_moves() {
  switch (Game::selectedPiece.first) {
  case 1:
  case 7:
    return get_pawn_moves();
  case 2:
  case 8:
    return get_knight_moves();
  case 3:
  case 9:
    return get_diagonal_moves();
  case 4:
  case 10:
    return get_rook_moves();
  case 5:
  case 11:
    return get_rook_moves() | get_diagonal_moves();
  case 6:
  case 12:
    return get_king_moves();
  default:
    return 0ULL;
  }
}

ull Game::get_pawn_moves() {
  ull legal_pawn_moves = 0ULL;

  // int direction = Game::white_turn ? -1 : 1;

  if (check_bit(allineone_bitboard, selectedPiece.first))
    ;

  return legal_pawn_moves;
}

ull get_knight_moves() { return 0; }
ull get_diagonal_moves() { return 0; }
ull get_rook_moves() { return 0; }
ull getKingMoves() { return 0; }
