#include "../include/fen.hpp"

void FEN::convertFEN() {
  f_enPassant = -1;
  f_whiteTurn = false;

  for (int i = 0; i < 4; i++)
    f_castle[i] = false;
  for (int i = 0; i < 64; i++)
    f_board[i] = '.';

  int cutoff = 0;
  for (int i = 0, k = 0; input[i] != ' '; i++) {
    cutoff = i + 1;
    if (input[i] == '/')
      continue;

    if (input[i] - '0' < 9)
      k += (input[i] - '0') - 1;
    else
      f_board[k] = input[i];
    k++;
  }

  f_whiteTurn = input[cutoff] == 'w' ? true : false;

  for (int i = cutoff + 3; input[i] != ' '; i++) {
    cutoff = i + 1;
    switch (input[i]) {
    case 'K':
      f_castle[0] = true;
      break;
    case 'Q':
      f_castle[1] = true;
      break;
    case 'k':
      f_castle[2] = true;
      break;
    case 'q':
      f_castle[3] = true;
      break;
    }
  }

  switch (input[cutoff + 1]) {
  case 'a':
    f_enPassant = 56;
    break;
  case 'b':
    f_enPassant = 57;
    break;
  case 'c':
    f_enPassant = 58;
    break;
  case 'd':
    f_enPassant = 59;
    break;
  case 'e':
    f_enPassant = 60;
    break;
  case 'f':
    f_enPassant = 61;
    break;
  case 'g':
    f_enPassant = 62;
    break;
  case 'h':
    f_enPassant = 63;
    break;
  default:
    f_enPassant = -1;
    break;
  }

  if (f_enPassant > 0)
    f_enPassant -= 8 * ((input[cutoff + 2] - '0') - 1);
}

FEN::FEN() { convertFEN(); }
