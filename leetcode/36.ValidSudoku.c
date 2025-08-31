#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * zeros out an occurrences array
 * @param unsigned int* occurrences occurrences Array
 * @param unsigned int size_occurrences Size of occurrences Array
 */
void resetOccurrences(unsigned int *occurrences,
                      unsigned int size_occurrences) {
  for (unsigned int i = 0; i < size_occurrences; ++i) {
    occurrences[i] = 0;
  }
}

bool isValidRows(char **board, int boardSize) {
  assert(boardSize == 9);

  // Init Occurrences Array which stores how many times we've seen a number
  const unsigned int size_occurrences = 9;
  unsigned int occurrences[size_occurrences];
  resetOccurrences(occurrences, size_occurrences);

  // Iterate through each row from up to down
  for (int row_idx = 0; row_idx < boardSize; ++row_idx) {
    char *row = *(board + row_idx);
    // Iterate through each column from left to right
    for (int col_idx = 0; col_idx < boardSize; ++col_idx) {
      char cell_value = *(row + col_idx);
      if (cell_value == '.') {
        continue;
      }
      unsigned int number = cell_value - '0';
      // occurrences index is offset by 1 from the number
      occurrences[number - 1] += 1;
      if (occurrences[number - 1] > 1) {
        return false;
      }
    }
    // The row is clean
    resetOccurrences(occurrences, size_occurrences);
  }
  return true;
}

/*
 * Experimented some more with C, I'm going to do this one a little different
 * than I did rows. Mainly to see if this can be done the way I'm going to
 * implement.
 */
bool isValidColumns(char **board, int boardSize) {
  assert(boardSize == 9);
  // Init Occurrences Array which stores how many times we've seen a number
  const unsigned int size_occurrences = 9;
  unsigned int occurrences[size_occurrences];
  resetOccurrences(occurrences, size_occurrences);
  // Iterate through each column from left to right
  for (unsigned int column_idx = 0; column_idx < boardSize; ++column_idx) {
    // Iterate through each row from up to down
    for (unsigned int row_idx = 0; row_idx < boardSize; ++row_idx) {
      char cell_value = board[row_idx][column_idx];
      // Pass over blank cells
      if (cell_value == '.') {
        continue;
      }
      unsigned int number = cell_value - '0';
      // occurrences index is offset by 1 from the number
      occurrences[number - 1] += 1;
      if (occurrences[number - 1] > 1) {
        return false;
      }
    }
    // The Column is Clean;
    resetOccurrences(occurrences, size_occurrences);
  }

  return true;
}

bool isValidSubSquares(char **board, unsigned int boardSize) {
  assert(boardSize == 9);
  // Init Occurrences Array which stores how many times we've seen a number
  const unsigned int size_occurrences = 9;
  unsigned int occurrences[size_occurrences];
  resetOccurrences(occurrences, size_occurrences);
  // Iterate through row_corner (top) indices
  for (unsigned int row_corner_idx = 0; row_corner_idx < boardSize;
       row_corner_idx += 3) {
    // iterate through column (left) indices
    //  Together we should be in the top left
    for (unsigned int column_corner_idx = 0; column_corner_idx < boardSize;
         column_corner_idx += 3) {
      // Time to start iterating through the actual Square
      // Maybe I should have made this a function to stop the nesting
      for (unsigned int row_offset = 0; row_offset < 3; ++row_offset) {
        for (unsigned int column_offset = 0; column_offset < 3;
             ++column_offset) {
          unsigned int row_idx = row_corner_idx + row_offset;
          unsigned int column_idx = column_corner_idx + column_offset;
          char value = board[row_idx][column_idx];
          if (value == '.') {
            continue;
          }
          unsigned int number = value - '0';
          // Occurences mapping to number is offset by 1 b/c legal numbers are
          // [1-9] and legal idx are [0-8]
          occurrences[number - 1] += 1;
          if (occurrences[number - 1] > 1) {
            return false;
          }
        }
      }
      // Prepare for next Square
      resetOccurrences(occurrences, size_occurrences);
    }
  }
  return true;
}

bool isValidSudoku(char **board, int boardSize, int *boardColSize) {
  return isValidColumns(board, boardSize) && isValidRows(board, boardSize) &&
         isValidSubSquares(board, boardSize);
}

int main() {
  char board_literal[9][9] = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                              {'6', '.', '3', '1', '9', '5', '.', '.', '.'},
                              {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                              {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                              {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                              {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                              {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                              {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                              {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  char *board[9];
  for (int i = 0; i < 9; ++i) {
    board[i] = board_literal[i];
  }
  unsigned int boardSize = 9;
  printf("%i\n", isValidRows(board, boardSize));
  printf("%i\n", isValidColumns(board, boardSize));
  printf("%i\n", isValidSubSquares(board, boardSize));
  printf("%i\n", isValidSudoku(board, boardSize, &boardSize));
  return EXIT_SUCCESS;
}
// vim: ts=2 sts=2 sw=2 et
