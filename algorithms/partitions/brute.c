/* Sam Auciello | 2013 | Algorithms Exam
 * This file solves the partition problem using a brute force approach
 */

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

// print a list of numbers as they would appear in a python list
void print_numbers(int* numbers, int size) {
  int i;
  printf("[ %d", numbers[0]);
  for (i = 1; i < size; i++) {
    printf(", %d", numbers[i]);
  }
  printf(" ]\n");
}

// print a partitioning of a list of numbers as a pair of python lists
void print_partitions(int* numbers, long subset, int size) {
  int i;
  printf("[");
  bool first = true;
  for (i = 0; i < size; i++) {
    if ((subset >> i) & 1) {
	  if (first) {
		first = false;
		printf(" %d", numbers[i]);
	  } else {
		printf(", %d", numbers[i]);
	  }
    }
  }
  printf(" ] [");
  first = true;
  for (i = 0; i < size; i++) {
    if (! ((subset >> i) & 1)) {
	  if (first) {
		first = false;
		printf(" %d", numbers[i]);
	  } else {
		printf(", %d", numbers[i]);
	  }
    }
  }
  printf(" ]\n");
}

// a counter to measure the complexity of the algorithm
long steps;

// Find a bitmap that partitions the list of numbers in to two disjoint sublists
// with equal sums.  Return -1 if none is found.
long partition(int* numbers, int size) {
  long subset;
  int i, left, right;
  long limit = (long)pow(2.0, (double)size);
  for (subset = 0; subset < limit; subset++) {
	steps++;
    left = right = 0;
    for (i = 0; i < size; i++) {
      if ((subset >> i) & 1) {
        left += numbers[i];
      } else {
        right += numbers[i];
      }
    }
    if (left == right) {
      return subset;
    }
  }
  return -1;
}

// run the partitioning algorithm on a given list of numbers and report the
// expected and measured complexity
void test(int* numbers, int size) {
  steps = 0;
  long subset = partition(numbers, size);
  print_numbers(numbers, size);
  if (subset < 0) {
    printf("no partitioning exists\n");
  } else {
    print_partitions(numbers, subset, size);
  }
  long limit = (long)pow(2.0, (double)size);
  printf("2^n:%li\n", limit);
  printf("steps:%li\n\n", steps);
}

int main() {

  int test1[5] = { 53, 24, 20, 81, 90 };
  test(test1, 5);
  
  int test2[5] = { 59, 54, 88, 86, 64 };
  test(test2, 5);
  
  int test3[10] = { 53, 55, 74, 44, 66, 1, 92, 34, 42, 57 };
  test(test3, 10);
  
  int test4[10] = { 2, 81, 10, 66, 50, 43, 22, 80, 89, 67 };
  test(test4, 10);
  
  int test5[20] = { 0, 0, 13, 0, 36, 40, 23, 38, 38, 25, 53, 37, 85, 10, 51, 1,
					74, 71, 33, 34 };
  test(test5, 20);
  
  int test6[20] = { 87, 68, 97, 55, 26, 48, 62, 48, 43, 80, 75, 13, 25, 62, 76,
					39, 3, 80, 37, 7 };
  test(test6, 20);
  
  int test7[50] = { 67, 78, 63, 45, 55, 13, 7, 75, 37, 84, 68, 68, 54, 4, 9, 90,
					70, 58, 39, 1, 19, 13, 33, 59, 88, 14, 98, 83, 69, 17, 87,
					61, 81, 21, 64, 19, 8, 71, 6, 34, 88, 8, 17, 69, 57, 94, 47,
					57, 4, 65 };
  test(test7, 50);
  
  return 0;
}
