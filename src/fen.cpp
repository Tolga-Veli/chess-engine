#include "../include/fen.hpp"

void FEN::convertFEN() {
  enPassant = -1;
  whiteTurn = false;
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

  whiteTurn = input[cutoff] == 'w' ? true : false;

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
    enPassant = 56;
    break;
  case 'b':
    enPassant = 57;
    break;
  case 'c':
    enPassant = 58;
    break;
  case 'd':
    enPassant = 59;
    break;
  case 'e':
    enPassant = 60;
    break;
  case 'f':
    enPassant = 61;
    break;
  case 'g':
    enPassant = 62;
    break;
  case 'h':
    enPassant = 63;
    break;
  default:
    enPassant = -1;
    break;
  }
  if (enPassant > 0)
    enPassant -= 8 * ((input[cutoff + 2] - '0') - 1);
}
