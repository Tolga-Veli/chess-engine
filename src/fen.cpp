#include "../include/fen.hpp"

void FEN::convertFEN() {
  en_passant = -1;
  white_turn = false;

  for (int i = 0; i < 4; i++)
    castle[i] = false;
  for (int i = 0; i < 64; i++)
    board[i] = '.';

  int cutoff = 0;
  for (int i = 0, k = 0; input[i] != ' '; i++) {
    cutoff = i + 1;
    if (input[i] == '/')
      continue;

    if (input[i] - '0' < 9)
      k += (input[i] - '0') - 1;
    else
      board[k] = input[i];
    k++;
  }

  white_turn = input[cutoff] == 'w' ? true : false;

  for (int i = cutoff + 3; input[i] != ' '; i++) {
    cutoff = i + 1;
    switch (input[i]) {
    case 'K':
      castle[0] = true;
      break;
    case 'Q':
      castle[1] = true;
      break;
    case 'k':
      castle[2] = true;
      break;
    case 'q':
      castle[3] = true;
      break;
    }
  }

  switch (input[cutoff + 1]) {
  case 'a':
    en_passant = 56;
    break;
  case 'b':
    en_passant = 57;
    break;
  case 'c':
    en_passant = 58;
    break;
  case 'd':
    en_passant = 59;
    break;
  case 'e':
    en_passant = 60;
    break;
  case 'f':
    en_passant = 61;
    break;
  case 'g':
    en_passant = 62;
    break;
  case 'h':
    en_passant = 63;
    break;
  default:
    en_passant = -1;
    break;
  }

  if (en_passant > 0)
    en_passant -= 8 * ((input[cutoff + 2] - '0') - 1);
}
