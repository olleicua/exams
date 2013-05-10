/* Sam Auciello | 2013 | languages Exam
 * A script to recursively search for solutions to a crossword of three digit
 * squares of the form:
 * #   # # #   # # #   #
 * # # #   # # #   # # #
 * #   # # #   # # #   #
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// A space in the crossword for a three digit square
struct _space {
  // the coordinate of the 0th digit
  int digit0_x;
  int digit0_y;
  // the coordinate of the 1st digit
  int digit1_x;
  int digit1_y;
  // the coordinate of the 2nd digit
  int digit2_x;
  int digit2_y;
  // a bit array denoting which digits will already have been written to when
  // this one is being considered.  A one in the most significant bit indicates
  // that the first digit of the square will not have overlap with  previously
  // written square.
  int write_array;
};

// a simple function to create a new space with the specified values
struct _space space(int digit0_x, int digit0_y, int digit1_x, int digit1_y,
					int digit2_x, int digit2_y, int write_array) {
  struct _space result;
  result.digit0_x = digit0_x;
  result.digit0_y = digit0_y;
  result.digit1_x = digit1_x;
  result.digit1_y = digit1_y;
  result.digit2_x = digit2_x;
  result.digit2_y = digit2_y;
  result.write_array = write_array;
  return result;
}

// initialize data structures used by the search

// an array of the available spaces
struct _space spaces[13];
 // a 2D array of the final crossword grid
int solution[3][11];
// an array of squares that have not yet been tried in the search
int unused_squares[22];
// a temporary array for swapping data with the unused_squares array
int unused_squares_tmp[22];
// the current size of the unused_squares array
int unused_squares_size;

// print out the final crossword grid
void print_solution() {
  int i, j;
  for (i = 0; i < 3; i++) {
	for (j = 0; j < 11; j++) {
	  if (solution[i][j] < 0) {
		printf("  ");
	  } else {
		printf(" %d", solution[i][j]);
	  }
	}
	printf("\n");
  }
}

// the standard integer campare function to be used with qsort
// taken from example at:
// http://www.anyexample.com/programming/c/qsort__sorting_array_of_strings__integers_and_structs.xml
int compare(const void* a, const void* b) {
  return (*(int*)a) - (*(int*)b);
}

// remove the specified square from the unused_squares list
void drop_from_unused_squares(int square) {
  int i, j;
  // copy to unused_squares_tmp
  for (i = 0; i < unused_squares_size; i++) {
	unused_squares_tmp[i] = unused_squares[i];
  }
  // copy back without the ommited square
  for (i = j = 0; i < unused_squares_size; i++) {
	if (unused_squares_tmp[i] != square) {
	  unused_squares[j] = unused_squares_tmp[i];
	  j++;
	}
  }
  unused_squares_size--;
  qsort(unused_squares, unused_squares_size, sizeof(int), compare);
}

// add the specified square to the unused_squares list
void add_to_unused_squares(int square) {
  unused_squares[unused_squares_size] = square;
  unused_squares_size++;
  qsort(unused_squares, unused_squares_size, sizeof(int), compare);
}

// try to write the specified square into the solution grid
// in the specified space
// returns true on success and false on failure
bool try_square(int square, struct _space space) {
  // check to see if there is a conflict in any of the digits that will already
  // have been written
  if ((((space.write_array & 4) == 0) &&
	   solution[space.digit0_y][space.digit0_x] != -1 &&
	   solution[space.digit0_y][space.digit0_x] != square / 100) ||
	  (((space.write_array & 2) == 0) &&
	   solution[space.digit1_y][space.digit1_x] != -1 &&
	   solution[space.digit1_y][space.digit1_x] != (square / 10) % 10) ||
	  (((space.write_array & 1) == 0) &&
	   solution[space.digit2_y][space.digit2_x] != -1 &&
	   solution[space.digit2_y][space.digit2_x] != square % 10)) {
	return false;
  }
  // write the digits that have not yet been written
  if (space.write_array & 4) {
	solution[space.digit0_y][space.digit0_x] = square / 100;
  }
  if (space.write_array & 2) {
	solution[space.digit1_y][space.digit1_x] = (square / 10) % 10;
  }
  if (space.write_array & 1) {
	solution[space.digit2_y][space.digit2_x] = square % 10;
  }
  return true;
}

// clear the digits from this space that were not previously written
void clear_space(struct _space space) {
  if (space.write_array & 4) {
	solution[space.digit0_y][space.digit0_x] = -1;
  }
  if (space.write_array & 2) {
	solution[space.digit1_y][space.digit1_x] = -1;
  }
  if (space.write_array & 1) {
	solution[space.digit2_y][space.digit2_x] = -1;
  }
}

// recursively search for a solution starting with the space denoted by the
// specified index into the spaces array
bool search(int space) {
  if (space == 13) { // base case
	return true;
  }
  
  int i, square;
  // try each unused square here
  for (i = 0; i < unused_squares_size; i++) {
	square = unused_squares[i];
	if (try_square(square, spaces[space])) {
	  drop_from_unused_squares(square);
	  if (search(space + 1)) {
		return true;
	  }
	  clear_space(spaces[space]);
	  add_to_unused_squares(square);
	}
  }
  return false;
}

int main() {
  
  // initialize
  int i, j;
  for (i = 0; i < 22; i++) {
	unused_squares[i] = (i + 10) * (i + 10);
  }
  unused_squares_size = 22;
  for (i = 0; i < 3; i++) {
	for (j = 0; j < 11; j++) {
	  solution[i][j] = -1;
	}
  }
  spaces[0] = space(0, 0, 0, 1, 0, 2, 7);
  spaces[1] = space(0, 1, 1, 1, 2, 1, 3);
  spaces[2] = space(2, 0, 2, 1, 2, 2, 5);
  spaces[3] = space(2, 0, 3, 0, 4, 0, 3);
  spaces[4] = space(2, 2, 3, 2, 4, 2, 3);
  spaces[5] = space(4, 0, 4, 1, 4, 2, 2);
  spaces[6] = space(4, 1, 5, 1, 6, 1, 3);
  spaces[7] = space(6, 0, 6, 1, 6, 2, 5);
  spaces[8] = space(6, 0, 7, 0, 8, 0, 3);
  spaces[9] = space(6, 2, 7, 2, 8, 2, 3);
  spaces[10] = space(8, 0, 8, 1, 8, 2, 2);
  spaces[11] = space(8, 1, 9, 1, 10, 1, 3);
  spaces[12] = space(10, 0, 10, 1, 10, 2, 5);
  
  // search
  search(0);
  print_solution();
  	
  return 0;
}