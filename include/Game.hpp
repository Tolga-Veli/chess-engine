#pragma once
#include "SDL_Handler.hpp"
#include <unordered_map>
#include <utility>
#define ull unsigned long long

/* enum bitboard_strings {
  Empty = 0,
  WhitePawn = 1,
  WhiteKnight,
  WhiteBishop,
  WhiteRook,
  WhiteQueen,
  WhiteKing,
  BlackPawn = 7,
  BlackKnight,
  BlackBishop,
  BlackRook,
  BlackQueen,
  BlackKing
}; */

class Game {
private:
  // Holds the bitboards for each piece
  std::unordered_map<bitboard_strings, ull> bitboards;

  // Holds the positions of all white piece
  ull white_bitboard;

  // Holds the positions of all black piece
  ull black_bitboard;

  // Holds the positions of all pieces
  ull allineone_bitboard;

  // Does a bitwise operation to check if a bit in _bitboard_ at position
  // _boardPos_ is 0 or 1
  bool check_bit(const ull &bitboard, int boardPos) const;

  // Flips the bit in _bitboard_ at pos _boardPos_
  void reverse_bit(ull &bitboard, int boardPos);

  // Clears the bit in _bitboard_ at pos _boardPos_
  void clear_bit(ull &bitboard, int boardPos);

  // Sets the bit in _bitboard_ at pos _boardPos_
  void set_bit(ull &bitboard, int boardPos);

  // Highlights legal moves
  void highlight_legal_moves();

  // Returns a bitboard of the available moves, where the bit is set - the move
  // is valid
  ull get_legal_moves();
  ull get_pawn_moves();
  ull get_knight_moves();
  ull get_diagonal_moves();
  ull get_rook_moves();
  ull get_king_moves();

public:
  // K-0, Q-1, k-2, q-3
  // 0 -> 7, 8 -> 15, -1 -> noEnPassant
  bool piece_selected = false;
  bool castle[4] = {false, false, false, false};
  int en_passant;
  bool white_turn = true;
  bool in_check = false;

  // Holds the enum for the selected piece and its index in the bitboards
  std::pair<bitboard_strings, int> selectedPiece;

  // Constructor to intialise all bitboards, FEN strings and set the values for
  // the bitboards;
  Game();

  // The logic and gui call for piece selection
  void select_piece(int index);

  // The logic and gui call for piece movement
  void move_piece(int index);
};
